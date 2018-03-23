#include <iostream>
#include "opencv2/opencv.hpp"

int main(int argc, char *argv[])
{
    cv::String imageName = "F:\\openCV\\workspace\\Tests\\data\\test.jpg";
    cv::Mat image;
    image = cv::imread(imageName,cv::IMREAD_COLOR);
    if(!image.data)
    {
        std::cout<<"image is null..."<<std::endl;
        return 0;
    }
    cv::Mat gray_image;
    cv::cvtColor(image,gray_image, cv::COLOR_BGR2GRAY);
    cv::imwrite("F:\\openCV\\workspace\\Tests\\data\\test_2gray.jpg",gray_image);
    cv::namedWindow(imageName,cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Gray image",cv::WINDOW_AUTOSIZE );
    cv::imshow(imageName,image);
    cv::imshow("Gray image",gray_image);
    cv::waitKey(0);
    return 0;
}
