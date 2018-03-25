#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"


using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat cat,dog;
    cat = imread("../data/test1.jpg");
    dog = imread("../data/dog.jpg");

    IplImage *pCat = &IplImage(cat);//! when use cvAnd ,you must deep copy. if you don't use cvCloneImage function,you can't get correct result.
    pCat = cvCloneImage(pCat);
    IplImage *pDog = &IplImage(dog);
    pDog = cvCloneImage(pDog);

    cvAnd(pCat,pDog,pCat);

    cat = cvarrToMat(pCat);
    imshow("and demo",cat);
    waitKey(0);
    return 0;
}
