#include<opencv2/opencv.hpp>
using namespace cv;
VideoCapture opencam(int cam_index)
{
    VideoCapture cap(cam_index); // open the default camera
    if (!cap.isOpened())  // check if we succeeded
    {
      return -1;
    }
    return cap;
}

