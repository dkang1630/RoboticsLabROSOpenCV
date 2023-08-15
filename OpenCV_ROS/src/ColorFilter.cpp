#include "opencv_hw/ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    // Mat BlueImg = getBlue();
    // Mat GreenImg = getGreen();
    // Mat RedImg = getRed();
    // Mat BGRImg = getBGR();
    // showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans); //why do i need to add cv? Is this the defaul cv built-in function?
}

void ColorFilter::showResult() {
    //display _frame
    // namedWindow("result");
    // namedWindow("channel_0");
    // namedWindow("channel_1");
    // namedWindow("channel_2");
    // namedWindow("final");
    // imshow("final", _frame);
    //imshow("result", _frame); //problem 1
    // imshow("channel_0", _chans[0]); //Problem 2 B
    // imshow("channel_1", _chans[1]); //Problem 2 G
    // imshow("channel_2", _chans[2]); //Problem 2 R
    // waitKey(200); //why do we need a waitkey for the video to play?
}

void ColorFilter::findBlue() {
    //Blue minus Red will show the blue darker
    Mat bMinusR;
    cv::subtract(_chans[0], _chans[2], bMinusR); //subtract Blue to Red
    // namedWindow("bMinusR");
    // imshow("bMinusR", bMinusR); //Problem 3 Blue Subtraction

    Mat thresh;
    cv::threshold(bMinusR, thresh, 50, 255, cv::THRESH_BINARY);
    // namedWindow("threshold");
    // imshow("threshold", thresh); //threshold image

    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy; //why do we need to call std and cv here?
    cv::findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0; //index of the contour that will be the biggest
    int maxContourSize = 0; //actual size of the contour
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourmaskB = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); //CV_8UC1 is a type of masking
    drawContours(contourmaskB, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    cv::Mat blueCupImg;
    _frame.copyTo(blueCupImg, contourmaskB); //only the pixels that are nonzero will be copied tp blueCupImg
    // _frame = blueCupImg;

}

void ColorFilter::findGreen() {
    //gMinusB will show the green darker
    Mat gMinusB;
    cv::subtract(_chans[1], _chans[0], gMinusB); //subtract green to blue
    // namedWindow("gMinusB");
    // imshow("gMinusB", gMinusB); //Problem 4 Green Subtraction

    Mat thresh;
    cv::threshold(gMinusB, thresh, 50, 255, cv::THRESH_BINARY);
    // namedWindow("threshold");
    // imshow("threshold", thresh); //threshold image

    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy; //why do we need to call std and cv here?
    cv::findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0; //index of the contour that will be the biggest
    int maxContourSize = 0; //actual size of the contour
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourmaskG = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); //CV_8UC1 is a type of masking
    drawContours(contourmaskG, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    cv::Mat greenCupImg;
    _frame.copyTo(greenCupImg, contourmaskG); //only the pixels that are nonzero will be copied tp blueCupImg
    // _frame = greenCupImg;
}

void ColorFilter::findRed() {
    //gMinusB will show the green darker
    Mat rMinusG;
    cv::subtract(_chans[2], _chans[1], rMinusG); //subtract green to blue
    // namedWindow("rMinusG");
    // imshow("rMinusG", rMinusG); //Problem 4 Green Subtraction

    Mat thresh;
    cv::threshold(rMinusG, thresh, 70, 255, cv::THRESH_BINARY);
    // namedWindow("threshold");
    // imshow("threshold", thresh); //threshold image

    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy; //why do we need to call std and cv here?
    cv::findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0; //index of the contour that will be the biggest
    int maxContourSize = 0; //actual size of the contour
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourmaskR = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); //CV_8UC1 is a type of masking
    drawContours(contourmaskR, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    cv::Mat redCupImg;
    _frame.copyTo(redCupImg, contourmaskR); //only the pixels that are nonzero will be copied tp blueCupImg
    // _frame = redCupImg;
}

Mat ColorFilter::returnMask(int ch_index_1, int ch_index_2) {
    Mat outputSubtract;
    cv::subtract(_chans[ch_index_1], _chans[ch_index_2], outputSubtract);

    Mat thresh;
    cv::threshold(outputSubtract, thresh, 50, 255, cv::THRESH_BINARY);

    std::vector<cv::Mat> contours;
    std::vector<cv::Vec4i> hierarchy; 
    cv::findContours(thresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    int maxSizeContour = 0; //index of the contour that will be the biggest
    int maxContourSize = 0; //actual size of the contour
    for (int i = 0; i < contours.size(); i++) {
        int contourSize = cv::contourArea(contours[i]);
        if (contourSize > maxContourSize) {
            maxSizeContour = i;
            maxContourSize = contourSize;
        }
    }
    
    cv::Mat contourmask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1); //CV_8UC1 is a type of masking
    drawContours(contourmask, contours, maxSizeContour, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    return contourmask; 
}
void ColorFilter::findBGR() {
    cv::Mat BlueMask = returnMask(0, 2);
    cv::Mat GreenMask = returnMask(1, 0);
    cv::Mat RedMask = returnMask(2, 1);

    cv::Mat BGMask;
    cv::Mat BGRMask;

    cv::bitwise_or(BlueMask, GreenMask, BGMask);
    cv::bitwise_or(BGMask, RedMask, BGRMask);

    cv::Mat BGRCupImg;
    _frame.copyTo(BGRCupImg, BGRMask); //only the pixels that are nonzero will be copied tp blueCupImg
    _frame = BGRCupImg;
}

Mat ColorFilter::getBlueImage() {
    cv::Mat BlueMask = returnMask(0, 2);
    cv::Mat BlueImg;
    _frame.copyTo(BlueImg, BlueMask);
    return BlueImg;
}

Mat ColorFilter::getGreenImage() {
    cv::Mat GreenMask = returnMask(1, 0);
    cv::Mat GreenImg;
    _frame.copyTo(GreenImg, GreenMask);
    return GreenImg;
}

Mat ColorFilter::getRedImage() {
    cv::Mat RedMask = returnMask(2, 1);
    cv::Mat RedImg;
    _frame.copyTo(RedImg, RedMask);
    return RedImg;
}

Mat ColorFilter::getBGRImage() {
    cv::Mat BlueMask = returnMask(0, 2);
    cv::Mat GreenMask = returnMask(1, 0);
    cv::Mat RedMask = returnMask(2, 1);

    cv::Mat BGMask;
    cv::Mat BGRMask;

    cv::bitwise_or(BlueMask, GreenMask, BGMask);
    cv::bitwise_or(BGMask, RedMask, BGRMask);

    cv::Mat BGRImg;
    _frame.copyTo(BGRImg, BGRMask); //only the pixels that are nonzero will be copied tp blueCupImg
    return BGRImg;
}