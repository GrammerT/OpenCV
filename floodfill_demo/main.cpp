#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;

Mat g_srcImage,g_dstImage,g_grayImage,g_maskImage;
int g_nFillMode = 1;
int g_nLowDifference = 20,g_nUpDifferent=20;

int g_nConnectivity = 4;
int g_bIsColor = true;
int g_bUseMask = false;
int g_nNewMaskVal=255;

static void ShowHelpText()
{
    //输出一些帮助信息
    printf("\n\n\n\t欢迎来到漫水填充示例程序~\n\n");
    printf( "\n\n\t按键操作说明: \n\n"
        "\t\t鼠标点击图中区域- 进行漫水填充操作\n"
        "\t\t键盘按键【ESC】- 退出程序\n"
        "\t\t键盘按键【1】-  切换彩色图/灰度图模式\n"
        "\t\t键盘按键【2】- 显示/隐藏掩膜窗口\n"
        "\t\t键盘按键【3】- 恢复原始图像\n"
        "\t\t键盘按键【4】- 使用空范围的漫水填充\n"
        "\t\t键盘按键【5】- 使用渐变、固定范围的漫水填充\n"
        "\t\t键盘按键【6】- 使用渐变、浮动范围的漫水填充\n"
        "\t\t键盘按键【7】- 操作标志符的低八位使用4位的连接模式\n"
        "\t\t键盘按键【8】- 操作标志符的低八位使用8位的连接模式\n"
        "\n\n\t\t\t\t\t\t\t\t by Grammer\n\n\n"
        );
}

static void onMouse(int event,int x,int y,int ,void *)
{
    if(event!=CV_EVENT_LBUTTONDOWN)
        return ;
    Point seed = Point(x,y);
    int lowDifference = g_nFillMode==0?0:g_nLowDifference;
    int upDifference = g_nFillMode==0?0:g_nUpDifferent;
    int flags = g_nConnectivity+(g_nNewMaskVal<<8)+(g_nFillMode==1?CV_FLOODFILL_FIXED_RANGE:0);

    int b = (unsigned)theRNG()&255;
    int g = (unsigned)theRNG()&255;
    int r = (unsigned)theRNG()&255;

    Rect ccomp;
    Scalar newVal = g_bIsColor?Scalar(b,g,r):Scalar(r*0.299+g*0.587+b*0.114);
    Mat dst = g_bIsColor?g_dstImage:g_grayImage;
    int area;
    if(g_bUseMask)
    {
        threshold(g_srcImage,g_maskImage,1,128,CV_THRESH_BINARY);
        area=floodFill(dst,g_maskImage,seed,newVal,&ccomp,Scalar(lowDifference,lowDifference,lowDifference),
                       Scalar(upDifference,upDifference,upDifference),flags);
        imshow("mask",g_maskImage);
    }
    else
    {
        area = floodFill(dst,seed,newVal,&ccomp,Scalar(lowDifference,lowDifference,lowDifference),
                         Scalar(upDifference,upDifference,upDifference),flags);

    }
    imshow("dst image" ,dst);
    cout<<area<<" pixels is painted..."<<endl;
}


int main(int argc, char *argv[])
{
    system("color 2F");
    g_srcImage = imread("../data/test1.jpg",1);
    if(!g_srcImage.data)
    {
        cout<<"open error...."<<endl;
        return 0;
    }
    ShowHelpText();

    g_srcImage.copyTo(g_dstImage);
    cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
    g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);

    namedWindow("dst image",CV_WINDOW_AUTOSIZE);

    createTrackbar("low","dst image",&g_nLowDifference,255,0);
    createTrackbar("up","dst image",&g_nUpDifferent,255,0);

    setMouseCallback("dst image",onMouse,0);

    while(1)
    {
        imshow("dst image",g_bIsColor?g_dstImage:g_grayImage);
        int c = waitKey(0);
        if((c&255)==27)
        {
            cout<<"exit..."<<endl;
            break;
        }
        switch ((char)c) {
        case '1':
        {
            if(g_bIsColor)
            {
                cout << "1  RGB--->GRAY\n";
                cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
                g_maskImage=Scalar::all(0);
                g_bIsColor = false;
            }
            else
            {
                cout << "1 GRAY---->RGB\n";
                g_srcImage.copyTo(g_dstImage);
                g_maskImage = Scalar::all(0);
                g_bIsColor = true;
            }
            break;
        }
        case '2':
        {
            if(g_bUseMask)
            {
                destroyWindow("mask");
                g_bUseMask = false;
            }
            else
            {
                namedWindow("mask",0);
                g_maskImage = Scalar::all(0);
                imshow("mask",g_maskImage);
                g_bUseMask= true;
            }
            break;
        }
        case '3':
        {
            cout<<"3  src image..."<<endl;
            g_srcImage.copyTo(g_dstImage);
            cvtColor(g_dstImage,g_grayImage,COLOR_BGR2GRAY);
            g_maskImage=Scalar::all(0);
            break;
        }
        case '4':
        {
            cout << "4 NULL range man shui\n";
            g_nFillMode = 0;
            break;
        }
        case '5':
        {
            cout << "5 range man shui\n";
            g_nFillMode = 1;
            break;
        }
        case '6':
        {
            cout << "6 dynamic man shui\n";
            g_nFillMode = 2;
            break;
        }
        case '7':
        {
            cout << "7 four bit connection type\n";
            g_nConnectivity = 4;
            break;
        }
        case '8':
        {
            cout << "8 eight bit connection type\n";
            g_nConnectivity = 8;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
