#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;
    cv::Mat returnMask(int ch_1, int ch_2);

  
    
public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    void showResult();

    cv::Mat getBlueImage();
    cv::Mat getGreenImage();
    cv::Mat getRedImage();
    cv::Mat getBGRImage();
};

#endif