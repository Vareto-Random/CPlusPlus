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
  { readme(); return -1; }

  cv::Mat img_object = cv::imread( argv[1], cv::IMREAD_GRAYSCALE );
  cv::Mat img_scene = cv::imread( argv[2], cv::IMREAD_GRAYSCALE );

  if( !img_object.data || !img_scene.data )
  { std::cout<< " --(!) Error reading images " << std::endl; return -1; }

  //-- Step 1: Detect the keypoints using SURF Detector
  int minHessian = 400;

  //SurfFeatureDetector detector1( minHessian );
  cv::Ptr<cv::Feature2D> sift = cv::xfeatures2d::SIFT::create();

  std::vector<cv::KeyPoint> keypoints_object, keypoints_scene;

  sift->detect( img_object, keypoints_object );
  sift->detect( img_scene, keypoints_scene );

  //-- Step 2: Calculate descriptors (feature vectors)
  //SurfDescriptorExtractor extractor;

  cv::Mat descriptors_object, descriptors_scene;

  sift->compute( img_object, keypoints_object, descriptors_object );
  sift->compute( img_scene, keypoints_scene, descriptors_scene );

  //-- Step 3: Matching descriptor vectors using FLANN matcher
  cv::FlannBasedMatcher matcher;
  std::vector< cv::DMatch > matches;
  matcher.match( descriptors_object, descriptors_scene, matches );

  double max_dist = 0; double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  for( int i = 0; i < descriptors_object.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  printf("-- Max dist : %f \n", max_dist );
  printf("-- Min dist : %f \n", min_dist );

  //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
  std::vector< cv::DMatch > good_matches;

  for( int i = 0; i < descriptors_object.rows; i++ )
  { if( matches[i].distance < 3*min_dist )
     { good_matches.push_back( matches[i]); }
  }

  cv::Mat img_matches;
  drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
               good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
               std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

  //-- Localize the object
  std::vector<cv::Point2f> obj;
  std::vector<cv::Point2f> scene;

  for( int i = 0; i < good_matches.size(); i++ )
  {
    //-- Get the keypoints from the good matches
    obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
    scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
  }

  cv::Mat H = findHomography( obj, scene, cv::RANSAC );

  //-- Get the corners from the image_1 ( the object to be "detected" )
  std::vector<cv::Point2f> obj_corners(4);
  obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
  obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
  std::vector<cv::Point2f> scene_corners(4);

  perspectiveTransform( obj_corners, scene_corners, H);

  //-- Draw lines between the corners (the mapped object in the scene - image_2 )
  line( img_matches, scene_corners[0] + cv::Point2f( img_object.cols, 0), scene_corners[1] + cv::Point2f( img_object.cols, 0), cv::Scalar(0, 255, 0), 4 );
  line( img_matches, scene_corners[1] + cv::Point2f( img_object.cols, 0), scene_corners[2] + cv::Point2f( img_object.cols, 0), cv::Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[2] + cv::Point2f( img_object.cols, 0), scene_corners[3] + cv::Point2f( img_object.cols, 0), cv::Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[3] + cv::Point2f( img_object.cols, 0), scene_corners[0] + cv::Point2f( img_object.cols, 0), cv::Scalar( 0, 255, 0), 4 );

  //-- Show detected matches
  cv::imshow( "Good Matches & Object detection", img_matches );

  cv::waitKey(0);
  return 0;
  }

  /** @function readme */
  void readme()
  { 
    std::cout << " Usage: ./SURF_descriptor <img1> <img2>" << std::endl; 
  }