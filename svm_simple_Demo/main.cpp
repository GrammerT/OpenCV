#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"
using namespace cv;
using namespace std;
using namespace cv::ml;
int main(int argc, char *argv[])
{
    int width = 512,height=512;
    Mat image = Mat::zeros(height,width,CV_8UC3);

    //! set up training data
    int labels[4]={1,-1,-1,-1};
    float trainingData[4][2]=
                            {{501,10},{255,10},
                              {501,255},{10,501}};
    Mat tainingDataMat(4,2,CV_32FC1,trainingData);
    Mat labelsMat(4,1,CV_32SC1,labels);
    //! train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER,100,1e-6));
    svm->train(tainingDataMat,ROW_SAMPLE,labelsMat);
    //! show the decision region given by SVM
    Vec3b green(0,255,0),blue(255,0,0);
    for(int i=0;i<image.rows;++i)
    {
        for(int j=0;j<image.cols;++j)
        {
            Mat sample=(Mat_<float>(1,2)<<j,i);
            float response = svm->predict(sample);
            if(response==1)
            {
                image.at<Vec3b>(i,j)=green;
            }
            else
            {
                image.at<Vec3b>(i,j)=blue;
            }
        }
    }
    //! show the training data
    int thickness = -1;
    int lineType = 8;
    circle(image,Point(501,10),5,Scalar(0,0,0),thickness,lineType);
    circle(image,Point(255,10),5,Scalar(255,255,255),thickness,lineType);
    circle(image,Point(501,255),5,Scalar(255,255,255),thickness,lineType);
    circle(image,Point(10,501),5,Scalar(255,255,255),thickness,lineType);

    //! show support vectors
    thickness = 2;
    lineType = 8;
    Mat sv = svm->getUncompressedSupportVectors();
    for(int i=0;i<sv.rows;++i)
    {
        const float *v=sv.ptr<float>(i);
        circle(image,Point((int)v[0],(int)v[1]),6,
                Scalar(128,128,128),thickness,lineType);
    }
    imwrite("result.png",image);
    imshow("svm demo",image);
    waitKey(0);
    return 0;
}
