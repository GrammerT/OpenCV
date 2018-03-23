#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

int main(int argc, char *argv[])
{
    cv::Mat mat(2,2,CV_8UC3,cv::Scalar(0,0,225));
    std::cout<<"M= "<<mat<<std::endl;
    std::cout<<std::endl;
//    int sz[3] = {2,2,2};
//    cv::Mat L(3,sz,CV_8UC1,cv::Scalar::all(0));
//    std::cout<<L<<std::endl;
    cv::Mat mat1;
    mat1.create(4,4,CV_8UC(2));
    std::cout<<"Mat1 --->"<<mat1<<std::endl;
    cv::Mat C = (cv::Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    std::cout << "C = " << std::endl << " " << C << std::endl << std::endl;
    cv::Mat r = cv::Mat(3,2,CV_8UC3);
    cv::randu(r,cv::Scalar::all(0),cv::Scalar::all(255));
    std::cout<<r<<std::endl;
    //! python format
    std::cout<<"R (python)--->"<<cv::format(r,cv::Formatter::FMT_PYTHON)<<std::endl;;
    std::cout<<"R (Numpy)--->"<<cv::format(r,cv::Formatter::FMT_NUMPY)<<std::endl;;
    std::cout<<"R (C)--->"<<cv::format(r,cv::Formatter::FMT_C)<<std::endl;;

   while(1);
    return 0;
}
