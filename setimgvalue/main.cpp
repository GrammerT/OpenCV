#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <string>


int main(int argc, char *argv[])
{
    std::cout << "Hello OpenCV!" << std::endl;
    cv::String imageName("F:\\openCV\\workspace\\Tests\\data\\test.jpg");
    if(argc>1)
    {
        imageName = argv[1];
    }
    cv::Mat image;
    image = cv::imread(imageName,cv::IMREAD_COLOR);
    if(image.empty())
    {
        std::cout<<"can't find the image..."<<std::endl;
        return 0;
    }
    cv::namedWindow("Display window",cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window",image);
    cv::waitKey(0);
    return 0;
}
