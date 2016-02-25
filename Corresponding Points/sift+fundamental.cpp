#include <stdio.h>
#include <iostream>

#include "opencv/cv.hpp" 
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"

//using namespace cv;
//using namespace cv::xfeatures2d;
//using namespace std;

void readme();

/** @function main */
int main( int argc, char** argv )
{
	if( argc != 3 )
	{ 
		readme(); 
		return -1; 
	}

	cv::Mat imageA = cv::imread( argv[1], cv::IMREAD_GRAYSCALE );
	cv::Mat imageB = cv::imread( argv[2], cv::IMREAD_GRAYSCALE );

	if( !imageA.data || !imageB.data )
	{ 
		std::cout<< " --(!) Error reading images " << std::endl; 
		return -1; 
	}

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	//SurfFeatureDetector detector1( minHessian );
	cv::Ptr<cv::Feature2D> sift = cv::xfeatures2d::SIFT::create();

	std::vector<cv::KeyPoint> keypoints_object, keypoints_scene;

	sift->detect( imageA, keypoints_object );
	sift->detect( imageB, keypoints_scene );

	//-- Step 2: Calculate descriptors (feature vectors)
	//SurfDescriptorExtractor extractor;

	cv::Mat descriptors_object, descriptors_scene;

	sift->compute( imageA, keypoints_object, descriptors_object );
	sift->compute( imageB, keypoints_scene, descriptors_scene );

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	cv::FlannBasedMatcher matcher;
	std::vector< cv::DMatch > matches;
	matcher.match( descriptors_object, descriptors_scene, matches );

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		double dist = matches[i].distance;
		if( dist < min_dist ) 
			min_dist = dist;
		if( dist > max_dist ) 
			max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist );
	printf("-- Min dist : %f \n", min_dist );

	//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
	std::vector< cv::DMatch > good_matches;

	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		if( matches[i].distance < 2*min_dist )
		{ 
			good_matches.push_back( matches[i]); 
		}
	}

	cv::Mat img_matches;
	drawMatches( imageA, keypoints_object, imageB, keypoints_scene,
			good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//-- Localize the object
	std::vector<cv::Point2f> pointsA;
	std::vector<cv::Point2f> pointsB;

	for( int i = 0; i < good_matches.size(); i++ )
	{
		//-- Get the keypoints from the good matches
		pointsA.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
		pointsB.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
	}

	//std::vector<cv::Point2f> pointsB;

	cv::Mat H = findHomography( pointsA, pointsB, cv::RANSAC );
	std::cout << H << std::endl;

	cv::Mat fundamental = cv::findFundamentalMat(
        cv::Mat(pointsA),
        cv::Mat(pointsB),
        CV_FM_8POINT
    );

    std::vector<cv::Vec3f> linesInImageB;
    
    cv::computeCorrespondEpilines(
    	cv::Mat(pointsA),
    	1,
    	fundamental,
    	linesInImageB
    );

    cv::Mat imageR = imageB.clone();
    for(std::vector<cv::Vec3f>::const_iterator it = linesInImageB.begin();
    	it != linesInImageB.end();
    	it++) {
    	cv::line(
    		imageR,
    		cv::Point(0, -(*it)[2]/(*it)[1]),
    		cv::Point(imageR.cols, -((*it)[2] + (*it)[0] * imageR.cols / (*it)[1])),
    		cv::Scalar(200,200,200)
    	);
    }

    std::vector<cv::KeyPoint> keypoints;
    for (cv::Point2f point : pointsA) {
    	keypoints.push_back(cv::KeyPoint(point, 1.f));
    }

    //cv::resize(imageR, imageR, cv::Size(900, 600));
    cv::imshow("Result Image", imageR);
    cv::waitKey(0);

	return 0;
}

/** @function readme */
void readme()
{ 
	std::cout << " Usage: ./SURF_descriptor <img1> <img2>" << std::endl; 
}