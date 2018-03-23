#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

// Declare the variables
Mat src,dst;
int top,bottom;
int left1,right1;
int borderType = BORDER_CONSTANT;

const char* window_name = "copyMakeBorder Demo";
const char* window_name1 = "copyMakeBorder Demo1";
RNG rng(12345);

int main(int argc, char *argv[])
{
    const char *imageName  = "../data/test_2gray.jpg";
    // Loads an image
    src = imread(imageName);
    if(src.empty())
    {
        cout<<"image error..."<<endl;
        return -1;
    }
    imshow(window_name1,src);
    // Brief how-to for this program
    printf( "\n \t copyMakeBorder Demo: \n" );
    printf( "\t -------------------- \n" );
    printf( " ** Press 'c' to set the border to a random constant value \n");
    printf( " ** Press 'r' to set the border to be replicated \n");
    printf( " ** Press 'ESC' to exit the program \n");
    namedWindow(window_name);
    // Initialize arguments for the filter

    top = (int) (0.05*src.rows);
    bottom = top;
    left1= (int) (0.05*src.cols);
    right1 = left1;
    for(;;)
    {
        Scalar value(rng.uniform(0,255),rng.uniform(0,2550),rng.uniform(0,255));
        copyMakeBorder(src,dst,top,bottom,left1,right1,borderType,value);
        imshow(window_name,dst);
        char c = (char)waitKey(500);
        if( c == 27 )
        { break; }
        else if( c == 'c' )
        { borderType = BORDER_CONSTANT; }
        else if( c == 'r' )
        { borderType = BORDER_REPLICATE; }
    }
    return 0;
}
