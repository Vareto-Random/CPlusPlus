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

	// Read source image.
    imageA = cv::imread("lab-left.jpg");
    // Four corners of the book in source image
    std::vector<cv::Point2f> pointsA;
    pointsA.push_back(cv::Point2f(312, 34));
    pointsA.push_back(cv::Point2f(512, 32));
    pointsA.push_back(cv::Point2f(310, 116)); 
    pointsA.push_back(cv::Point2f(408, 137));
    pointsA.push_back(cv::Point2f(447, 140));
    pointsA.push_back(cv::Point2f(486, 143));
    pointsA.push_back(cv::Point2f(527, 148));
    pointsA.push_back(cv::Point2f(569, 150));
    pointsA.push_back(cv::Point2f(182, 245));
    pointsA.push_back(cv::Point2f(323, 253));
    pointsA.push_back(cv::Point2f(375, 260));
    pointsA.push_back(cv::Point2f(429, 266));
    pointsA.push_back(cv::Point2f(488, 276));
    pointsA.push_back(cv::Point2f(540, 249));
    pointsA.push_back(cv::Point2f(97, 305));
    pointsA.push_back(cv::Point2f(101, 410));
    pointsA.push_back(cv::Point2f(131, 424));

    // Read destination image.
    imageB = cv::imread("lab-right.jpg");
    // Four corners of the book in destination image.
    std::vector<cv::Point2f> pointsB;
    pointsA.push_back(cv::Point2f(131, 46));
    pointsA.push_back(cv::Point2f(327, 14));
    pointsA.push_back(cv::Point2f(268, 116)); 
    pointsA.push_back(cv::Point2f(301, 128));
    pointsA.push_back(cv::Point2f(341, 122));
    pointsA.push_back(cv::Point2f(380, 118));
    pointsA.push_back(cv::Point2f(415, 115));
    pointsA.push_back(cv::Point2f(451, 111));
    pointsA.push_back(cv::Point2f(341, 270));
    pointsA.push_back(cv::Point2f(363, 246));
    pointsA.push_back(cv::Point2f(416, 237));
    pointsA.push_back(cv::Point2f(466, 228));
    pointsA.push_back(cv::Point2f(512, 219));
    pointsA.push_back(cv::Point2f(568, 178));
    pointsA.push_back(cv::Point2f(352, 369));
    pointsA.push_back(cv::Point2f(537, 440));
    pointsA.push_back(cv::Point2f(575, 427));

    fundamental = cv::findFundamentalMat(
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