#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"

int threshold_type;
int maxValue;

int main(int argc, char *argv[])
{
    String src_path;
    src_path+=DATA_PATH;
    src_path += "test1.jpg";
    Mat src = imread(src_path);
    Mat dst;
    if(src.empty())
    {
        cout<<"image error..."<<endl;
        return 0;
    }
    imshow("src demo",src);

//    while(waitKey(9)!='q')
    {
        threshold(src,dst,100,150,THRESH_BINARY);//! if src's pixel >100 dst's pixel = 150 otherwise =0
        imshow("dst demo THRESH_BINARY",dst);
    }
    threshold(src,dst,100,150,THRESH_BINARY_INV);//! if src's pixel >100 dst's pixel = 0 otherwise =150
    imshow("dst demo THRESH_BINARY_INV",dst);

    threshold(src,dst,100,150,THRESH_TRUNC);//! if src's pixel >100 dst's pixel = 100 otherwise : dst's = src's
    imshow("dst demo THRESH_TRUNC",dst);

    threshold(src,dst,100,150,THRESH_TOZERO);//! if src's pixel < 100 dst's pixel = 0 otherwise : dst's = src's
    imshow("dst demo THRESH_TOZERO",dst);

    threshold(src,dst,100,150,THRESH_TOZERO_INV);//! if src's pixel > 100 dst's pixel = 0 otherwise : dst's = src's
    imshow("dst demo THRESH_TOZERO_INV",dst);
    vector<Mat> v_src;
    split(src,v_src);
    Mat src_single = v_src[0];
    imshow("src_single",src_single);
    {
        threshold(src_single,dst,100,150,THRESH_BINARY);//! if src's pixel >100 dst's pixel = 150 otherwise =0
        imshow("dst_single demo THRESH_BINARY",dst);
    }
    threshold(src_single,dst,100,150,THRESH_BINARY_INV);//! if src's pixel >100 dst's pixel = 0 otherwise =150
    imshow("dst_single demo THRESH_BINARY_INV",dst);

    threshold(src_single,dst,100,150,THRESH_TRUNC);//! if src's pixel >100 dst's pixel = 100 otherwise : dst's = src's
    imshow("dst_single demo THRESH_TRUNC",dst);

    threshold(src_single,dst,100,150,THRESH_TOZERO);//! if src's pixel < 100 dst's pixel = 0 otherwise : dst's = src's
    imshow("dst_single demo THRESH_TOZERO",dst);

    threshold(src_single,dst,100,150,THRESH_TOZERO_INV);//! if src's pixel > 100 dst's pixel = 0 otherwise : dst's = src's
    imshow("dst_single demo THRESH_TOZERO_INV",dst);
    waitKey(0);
    return 0;
}
