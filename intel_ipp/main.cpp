#include <iostream>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;
#ifdef HAVE_IPP_A
#include "opencv2/core/ippasync.hpp"
#define CHECK_STATUS(STATUS, NAME)\
    if(STATUS!=HPP_STATUS_NO_ERROR){ printf("%s error %d\n", NAME, STATUS);\
    if (virtMatrix) {hppStatus delSts = hppiDeleteVirtualMatrices(accel, virtMatrix); CHECK_DEL_STATUS(delSts,"hppiDeleteVirtualMatrices");}\
    if (accel)      {hppStatus delSts = hppDeleteInstance(accel); CHECK_DEL_STATUS(delSts, "hppDeleteInstance");}\
    return -1;}
#define CHECK_DEL_STATUS(STATUS, NAME)\
    if(STATUS!=HPP_STATUS_NO_ERROR){ printf("%s error %d\n", NAME, STATUS); return -1;}
#endif

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}
