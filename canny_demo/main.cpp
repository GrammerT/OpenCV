#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

//#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
#define DATA_PATH "..\\data\\"

int main(int argc, char *argv[])
{
    String src_path ;
    src_path+=DATA_PATH;
    src_path+="test1.jpg";
    Mat src = imread(src_path);
    if(src.empty())
    {
        cout<<"src error...\n";
        return 0;
    }
    Mat src_c = src.clone();
    imshow("Canny demo src",src);
    Mat dst_canny;
    Canny(src,dst_canny,150,100);
    imshow("Canny demo dst",dst_canny);

    Mat dst,edge,gray;
    dst.create(src_c.size(),src_c.type());
    cvtColor(src_c,gray,CV_BGR2GRAY);
    blur(gray,edge,Size(3,3));
    Mat edge_canny;
    Canny(edge,edge_canny,3,9,3);
    dst = Scalar::all(0);
    imshow("src_c demo",src_c);

    src_c.copyTo(dst,edge_canny);
    imshow("edge_canny2",dst);
    waitKey(0);
    return 0;
}
