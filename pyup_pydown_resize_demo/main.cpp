#include <iostream>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
#define DATA_PATH "D:\\Opensource workspace\\openCV\\workspace\\Tests\\data\\"
static void ShowHelpText()
{
    printf( "\n\n\tintroduction: \n\n"
        "\t\tESC- exit\n"
        "\t\t1- resize big\n"
        "\t\t2- resize little\n"
        "\t\t3- pyrUp big\n"
        "\t\t4- pyrDown little\n"
            "\t\t5- recovery\n"
        "\n\n\t\t\t\t\t\t\t\t by  Grammer -->from qianmo\n\n\n"
        );
}

Mat g_srcImage,g_dstImage,g_tmpImage;

int main(int argc, char *argv[])
{
    ShowHelpText();
    String str;
    str+=DATA_PATH;
    str+="test1.jpg";
    g_srcImage = imread(str);
    if(g_srcImage.empty())
    {
        cout<<"src error..."<<endl;
        return 0;
    }
    namedWindow("src image",CV_WINDOW_AUTOSIZE);
    imshow("src image",g_srcImage);
    g_tmpImage = g_srcImage;
    g_dstImage = g_tmpImage;
    int key = 0;
    while(1)
    {
        key = waitKey(9);
        switch (key) {
        case 'q':
        {
            return 0;
            break;
        }
        case '1':
        {
            resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
            cout<<"image bigger by resize()...\n";
            break;
        }
        case '2':
        {
            resize(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2),(0,0),(0,0),2);
            break;
        }
        case '3':
        {
            pyrUp(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
            break;
        }
        case '4':
        {
            pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
            break;
        }
        case '5':
        {
            g_dstImage = g_srcImage;
            break;
        }
        default:
            break;
        }
        imshow("dst image",g_dstImage);
        g_tmpImage = g_dstImage;
    }
    return 0;
}
