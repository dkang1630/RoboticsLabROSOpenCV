#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv_hw/ColorFilter.h"
#include "opencv_hw/ROSInterface.h"


int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");

  ColorFilter cf;
  ROSInterface ri(cf);
  ros::spin();
  return 0;
}