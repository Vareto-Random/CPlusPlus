#include <stdio.h>
#include <iostream>

#include "opencv/cv.hpp" 
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/xfeatures2d.hpp"

int main (int argc, char** argv) {
	if (argc > 1) {
		cv::Mat img_object = cv::imread( argv[1], cv::IMREAD_GRAYSCALE );
		cv::Mat img_scene = cv::imread( argv[2], cv::IMREAD_GRAYSCALE );
	}

    cv::Mat imageA, imageB, fundamental;

	// // Read source image.
 //    imageA = cv::imread("0004.jpg");
 //    // Four corners of the book in source image
 //    std::vector<cv::Point2f> pointsA;
 //    pointsA.push_back(cv::Point2f(1054, 127));
 //    pointsA.push_back(cv::Point2f(1698, 863));
 //    pointsA.push_back(cv::Point2f(1702, 1055));
 //    pointsA.push_back(cv::Point2f(1706, 1295));
 //    pointsA.push_back(cv::Point2f(2630, 931));
 //    pointsA.push_back(cv::Point2f(2642, 1103));
 //    pointsA.push_back(cv::Point2f(2650, 1295));
 //    pointsA.push_back(cv::Point2f(2962, 367));

 //    // Read destination image.
 //    imageB = cv::imread("0011.jpg");
 //    // Four corners of the book in destination image.
 //    std::vector<cv::Point2f> pointsB;
 //    pointsB.push_back(cv::Point2f(169, 705));
 //    pointsB.push_back(cv::Point2f(374, 1103));
 //    pointsB.push_back(cv::Point2f(362, 1255));
 //    pointsB.push_back(cv::Point2f(342, 1439));
 //    pointsB.push_back(cv::Point2f(1058, 1023));
 //    pointsB.push_back(cv::Point2f(1054, 1207));
 //    pointsB.push_back(cv::Point2f(1046, 1435));
 //    pointsB.push_back(cv::Point2f(1606, 135));

 //    fundamental = cv::findFundamentalMat(
 //        cv::Mat(pointsA),
 //        cv::Mat(pointsB),
 //        CV_FM_8POINT
 //    );

    // Read source image.
    imageA = cv::imread("0006.jpg");
    // Four corners of the book in destination image.
    std::vector<cv::Point2f> pointsA;
    pointsA.push_back(cv::Point2f(460, 1304));
    pointsA.push_back(cv::Point2f(895, 1484));
    pointsA.push_back(cv::Point2f(1579, 1211));
    pointsA.push_back(cv::Point2f(2176, 1383));
    pointsA.push_back(cv::Point2f(2489, 1492));
    pointsA.push_back(cv::Point2f(2599, 1297));
    pointsA.push_back(cv::Point2f(1644, 381));

    // Read destination image.
    imageB = cv::imread("0007.jpg");
    // Four corners of the book in source image
    std::vector<cv::Point2f> pointsB;
    pointsB.push_back(cv::Point2f(232, 1368));
    pointsB.push_back(cv::Point2f(556, 1544));
    pointsB.push_back(cv::Point2f(1312, 1268));
    pointsB.push_back(cv::Point2f(1892, 1442));
    pointsB.push_back(cv::Point2f(2235, 1554));
    pointsB.push_back(cv::Point2f(2450, 1347));
    pointsB.push_back(cv::Point2f(1378, 436));

    fundamental = cv::findFundamentalMat(
        cv::Mat(pointsA),
        cv::Mat(pointsB),
        CV_FM_7POINT
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

    cv::resize(imageR, imageR, cv::Size(900, 600));
    cv::imshow("Result Image", imageR);
    cv::waitKey(0);

	return 0;
}