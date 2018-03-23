#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <sstream>

cv::Mat& ScanImageAndReduceC(cv::Mat &I,const uchar *table);
cv::Mat& ScanImageAndReduceIterator(cv::Mat &I,const uchar *table);
cv::Mat& ScanImageAndReduceRandomAccess(cv::Mat &I,const uchar *table);



int main(int argc, char *argv[])
{
    if(argc<3)
    {
        std::cout<<"Not enough parameters"<<std::endl;
        return 0;
    }
    cv::Mat I,J;
    if(argc==4&&!strcmp(argv[3],"G"))
    {
        I = cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
    }
    else
    {
        I = cv::imread(argv[1],cv::IMREAD_COLOR);
    }
    if(I.empty())
    {
        std::cout<<"The image "<<argv[1]<<" could not be loaded ."<<std::endl;
        return -1;
    }
    int divideWith = 0;
    std::stringstream s;
    s<<argv[2];
    s>>divideWith;
    if(!s||!divideWith)
    {
        std::cout<<"Invalid number entered for dividing. " << std::endl;
    }
    uchar table[256];
    for(int i=0;i<256;++i)
    {
        table[i] = (uchar)((divideWith)*(i/divideWith));
        std::cout<<(divideWith)*(i/divideWith)<<" ";
    }
    const int times = 100;
    double t;
    t=(double)cv::getTickCount();
    for(int i=0;i<times;++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceC(clone_i,table);
    }
    t = 1000*((double)cv::getTickCount()-t/cv::getTickFrequency());
    t/=times;
    std::cout << "Time of reducing with the C operator [] (averaged for "
    << times << " runs): " << t << " milliseconds."<< std::endl;
    t = (double)cv::getTickCount();
    for(int i=0;i<times;++i)
    {
        cv::Mat clone_i = I.clone();
        J = ScanImageAndReduceIterator(clone_i,table);
    }
    t=1000*((double)cv::getTickCount()-t/cv::getTickFrequency());
    t/=times;
    std::cout << "Time of reducing with the iterator (averaged for "
    << times << " runs): " << t << " milliseconds."<< std::endl;

    t= (double)cv::getTickCount();
    for(int i=0;i<times;++i)
    {
        cv::Mat clone_i = I.clone();
        ScanImageAndReduceRandomAccess(clone_i,table);
    }
    t=1000*((double)cv::getTickCount()-t)/cv::getTickFrequency();
    t/=times;

    std::cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
    << times << " runs): " << t << " milliseconds."<< std::endl;


    //! table init
    cv::Mat lookupTable(1,256,CV_8U);
    uchar* p = lookupTable.ptr();
    for(int i=0;i<256;++i)
    {
        p[i] = table[i];
    }
    t=(double)cv::getTickCount();
    for(int i=0;i<times;++i)
    {
        cv::LUT(I,lookupTable,J);
    }
    t = 1000*((double)cv::getTickCount()-t/cv::getTickFrequency());
    t/=times;
    std::cout << "Time of reducing with the LUT function (averaged for "
    << times << " runs): " << t << " milliseconds."<< std::endl;

    return 0;
}

cv::Mat& ScanImageAndReduceC(cv::Mat &I,const uchar *table)
{
    CV_Assert(I.depth()==CV_8U);
    int channels = I.channels();
    int nRows = I.rows;
    int nCols = I.cols*channels;
    if(I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }
    int i,j;
    uchar *p;
    for(i=0;i<nRows;++i)
    {
        p = I.ptr<uchar>(i);
        for(j=0;j<nCols;++j)
        {
            p[j]=table[p[j]];
        }
    }
    cv::imwrite("F:\\openCV\\workspace\\Tests\\data\\test_reduceC.jpg",I);
    return I;
}

cv::Mat& ScanImageAndReduceIterator(cv::Mat &I,const uchar *table)
{
    CV_Assert(I.depth()==CV_8U);
    const int channels = I.channels();
    switch(channels)
    {
    case 1:
    {
        cv::MatIterator_<uchar> it,end;
        for(it=I.begin<uchar>(),end=I.end<uchar>();it!=end;++it)
        {
            *it = table[*it];
        }
        break;
    }
    case 2:
    {

    }
    case 3:
    {
        cv::MatIterator_<cv::Vec3b> it,end;
        for(it=I.begin<cv::Vec3b>(),end = I.end<cv::Vec3b>();it!=end;++it)
        {
            (*it)[0] = table[(*it)[0]];
            (*it)[1] = table[(*it)[1]];
            (*it)[2] = table[(*it)[2]];
        }
    }
    }
    cv::imwrite("F:\\openCV\\workspace\\Tests\\data\\test_reduceItor.jpg",I);
    return I;
}

cv::Mat& ScanImageAndReduceRandomAccess(cv::Mat &I,const uchar *table)
{
    CV_Assert(I.depth()==CV_8U);
    const int channels = I.channels();
    switch(channels)
    {
        case 1:
        {
            for(int i=0;i<I.rows;++i)
            {
                for(int j=0;j<I.cols;++j)
                {
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
                }
            }
            break;
        }
        case 3:
        {
            cv::Mat_<cv::Vec3b> _I = I;
            for(int i=0;i<I.rows;++i)
                for(int j=0;j<I.cols;++j)
                {
                    _I(i,j)[0] = table[_I(i,j)[0]];
                    _I(i,j)[1] = table[_I(i,j)[1]];
                    _I(i,j)[2] = table[_I(i,j)[2]];
                }
            I = _I;
            break;
        }
    }
    cv::imwrite("F:\\openCV\\workspace\\Tests\\data\\test_reduceAccess.jpg",I);
    return I;
}
