#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H

#include "opencv_hw/ColorFilter.h"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/image_encodings.h>

class ROSInterface {
    ros::NodeHandle _nh;
    image_transport::ImageTransport _it;
    image_transport::Publisher _pubB;
    image_transport::Publisher _pubG;
    image_transport::Publisher _pubR;
    image_transport::Publisher _pubBGR;
    image_transport::Subscriber _sub;
    ColorFilter &_cf;

public: 
    ROSInterface(ColorFilter &cf);

    void callback(const sensor_msgs::ImageConstPtr &msg);

};
#endif