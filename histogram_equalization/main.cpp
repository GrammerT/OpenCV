#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

using namespace std;

int main(int argc, char *argv[])
{
    Mat src, dst;
    const char* source_window = "Source image";
    const char* equalized_window = "Equalized Image";

    CommandLineParser parser( argc, argv, "{@input | ../data/test1.jpg | input image}" );
    src = imread( parser.get<String>( "@input" ), IMREAD_COLOR );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    cvtColor(src,dst,COLOR_RGB2GRAY);

    equalizeHist(dst,dst);
    namedWindow( source_window, WINDOW_AUTOSIZE );
    namedWindow( equalized_window, WINDOW_AUTOSIZE );
    imshow( source_window, src );
    imshow( equalized_window, dst );
    waitKey(0);

    return 0;
}
