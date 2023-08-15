#include "opencv_hw/ROSInterface.h"
#include "opencv_hw/ColorFilter.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/image_encodings.h>

using namespace std;
using namespace cv;

ROSInterface::ROSInterface(ColorFilter &cf) : _cf(cf), _it(_nh) {
    _sub = _it.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::callback, this);
    _pubB = _it.advertise("blue", 1);
    _pubG = _it.advertise("green", 1);
    _pubR = _it.advertise("red", 1);
    _pubBGR = _it.advertise("bgr", 1);

    
}

void ROSInterface::callback(const sensor_msgs::ImageConstPtr &msg) { //converting ROS image to OpenCV image
        cv_bridge::CvImagePtr cv_ptr;
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8); //BGR8 is the cv image; msg is in ROS format
        _cf.processImage(cv_ptr->image);
        Mat BlueImg = _cf.getBlueImage();
        Mat GreenImg = _cf.getGreenImage();
        Mat RedImg = _cf.getRedImage();
        Mat BGRImg = _cf.getBGRImage();

        sensor_msgs::ImagePtr msgBGR = cv_bridge::CvImage(std_msgs::Header(), "bgr8", BGRImg).toImageMsg();
        sensor_msgs::ImagePtr msgB = cv_bridge::CvImage(std_msgs::Header(), "bgr8", BlueImg).toImageMsg(); //openCV to ROS
        sensor_msgs::ImagePtr msgG = cv_bridge::CvImage(std_msgs::Header(), "bgr8", GreenImg).toImageMsg();
        sensor_msgs::ImagePtr msgR = cv_bridge::CvImage(std_msgs::Header(), "bgr8", RedImg).toImageMsg();

        _pubB.publish(msgB);
        _pubG.publish(msgG);
        _pubR.publish(msgR);
        _pubBGR.publish(msgBGR);

    }
