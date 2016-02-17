#include "opencv2/opencv.hpp" 
 
using namespace cv;
using namespace std;
 
int main( int argc, char** argv)
{
    // Read source image.
    Mat im_src = imread("0004.jpg");
    // Four corners of the book in source image
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(1054, 127));
    pts_src.push_back(Point2f(1698, 863));
    pts_src.push_back(Point2f(1702, 1055));
    pts_src.push_back(Point2f(1706, 1295));
    pts_src.push_back(Point2f(2630, 931));
    pts_src.push_back(Point2f(2642, 1103));
    pts_src.push_back(Point2f(2650, 1295));
    pts_src.push_back(Point2f(2962, 367));
 
 
    // Read destination image.
    Mat im_dst = imread("0011.jpg");
    // Four corners of the book in destination image.
    vector<Point2f> pts_dst;
    pts_dst.push_back(Point2f(169, 705));
    pts_dst.push_back(Point2f(374, 1103));
    pts_dst.push_back(Point2f(362, 1255));
    pts_dst.push_back(Point2f(342, 1439));
    pts_dst.push_back(Point2f(1058, 1023));
    pts_dst.push_back(Point2f(1054, 1207));
    pts_dst.push_back(Point2f(1046, 1435));
    pts_dst.push_back(Point2f(1606, 135));
 
    // Calculate Homography
    Mat h = findHomography(pts_src, pts_dst);
    cout << h << endl;
 
    // Output image
    Mat im_out;
    // Warp source image to destination based on homography
    warpPerspective(im_src, im_out, h, im_dst.size());
 
    // Display images
    //imshow("Source Image", im_src);
    //imshow("Destination Image", im_dst);
    //imshow("Warped Source Image", im_out);
 
    waitKey(0);
}