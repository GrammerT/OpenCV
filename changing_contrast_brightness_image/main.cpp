#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    double alpha = 1.0;
    int beta = 0;
    String imageName("F:\\openCV\\workspace\\Tests\\data\\test.jpg");
    Mat image = imread(imageName);
    Mat new_image = Mat::zeros(image.size(),image.type());
    cout << "* Enter the alpha value [1.0-3.0]: ";
    cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";
    cin >> beta;
    for(int y=0;y<image.rows;++y)
    {
        for(int x=0;x<image.cols;++x)
        {
            for(int c=0;c<3;++c)
            {
                //! saturate_cast:
                new_image.at<Vec3b>(y,x)[c]=
                        saturate_cast<uchar>(alpha*(image.at<Vec3b>(y,x)[c])+beta);
            }
        }
    }
    namedWindow("Original Image");
    namedWindow("New Image");
    imshow("Original Image",image);
    imshow("New Image",new_image);
    waitKey();
    return 0;
}
