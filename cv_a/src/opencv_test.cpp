//
// Created by zander on 18-10-13.
//

/**
* @概述：采用FAST算子检测特征点，采用SIFT算子对特征点进行特征提取，并使用BruteForce匹配法进行特征点的匹配
* @类和函数：FastFeatureDetector + SiftDescriptorExtractor + BruteForceMatcher
*/


#include<opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int main(int argc, char** argv)
{
    Mat objImage = imread("1.jpg", IMREAD_COLOR);
    Mat sceneImage = imread("2.jpg", IMREAD_COLOR);
    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create(minHessian);
    std::vector<KeyPoint> obj_keypoint, scene_keypoint;
    detector->detect(objImage, obj_keypoint);
    detector->detect(sceneImage, scene_keypoint);
    //computer the descriptors
    Mat obj_descriptors, scene_descriptors;
    detector->compute(objImage, obj_keypoint, obj_descriptors);
    detector->compute(sceneImage, scene_keypoint, scene_descriptors);
    //use BruteForce to match,and get good_matches
    BFMatcher matcher;
    vector<DMatch> matches;
    matcher.match(obj_descriptors, scene_descriptors, matches);
    sort(matches.begin(), matches.end());  //筛选匹配点
    vector<DMatch> good_matches;
    for (int i = 0; i < min(50, (int)(matches.size()*0.15)); i++) {
        good_matches.push_back(matches[i]);
    }
    //draw matches
    Mat imgMatches;
    drawMatches(objImage, obj_keypoint, sceneImage, scene_keypoint,good_matches, imgMatches);
    //get obj bounding
    vector<Point2f> obj_good_keypoint;
    vector<Point2f> scene_good_keypoint;
    for (int i = 0; i < good_matches.size(); i++) {
        obj_good_keypoint.push_back(obj_keypoint[good_matches[i].queryIdx].pt);
        scene_good_keypoint.push_back(scene_keypoint[good_matches[i].trainIdx].pt);
    }
    vector<Point2f> obj_box(4);
    vector<Point2f> scene_box(4);
    obj_box[0] = Point(0, 0);
    obj_box[1] = Point(objImage.cols, 0);
    obj_box[2] = Point(objImage.cols, objImage.rows);
    obj_box[3] = Point(0, objImage.rows);
    Mat H = findHomography(obj_good_keypoint, scene_good_keypoint, RANSAC); //find the perspective transformation between the source and the destination
    perspectiveTransform(obj_box, scene_box, H);
    line(imgMatches, scene_box[0]+Point2f((float)objImage.cols, 0), scene_box[1] + Point2f((float)objImage.cols, 0), Scalar(0, 255, 0), 2);
    line(imgMatches, scene_box[1] + Point2f((float)objImage.cols, 0), scene_box[2] + Point2f((float)objImage.cols, 0), Scalar(0, 255, 0), 2);
    line(imgMatches, scene_box[2] + Point2f((float)objImage.cols, 0), scene_box[3] + Point2f((float)objImage.cols, 0), Scalar(0, 255, 0), 2);
    line(imgMatches, scene_box[3] + Point2f((float)objImage.cols, 0), scene_box[0] + Point2f((float)objImage.cols, 0), Scalar(0, 255, 0), 2);
    //show the result
    imshow("匹配图", imgMatches);
    //save picture file
    imwrite("final.jpg",imgMatches);
    waitKey(0);
    return 0;
}