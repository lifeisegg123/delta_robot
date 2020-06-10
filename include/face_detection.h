#ifndef Face_Detection
#define Face_detection
#include "opencv2/opencv.hpp"
#include <iostream>
#include "deltaServo.h"

using namespace cv;
using namespace cv::dnn;
using namespace std;

namespace delta
{
    class FaceDetector
    {
    public:
        FaceDetector(const int cam_number = 0);
        int init();
        int getImage();
        void detectFace();
        void getEdges();
        void putLabel(const float &confidence, const int &x, const int &y);
        void searchPixel();
        int showImages();
        Mat getFrame() const;
        Mat getDst() const;

    private:
        const String model = "../model/opencv_face_detector_uint8.pb";
        const String config = "../model/opencv_face_detector.pbtxt";
        VideoCapture cap;
        Net net;

        Mat frame;
	    Rect faceRect;
	    Mat face;
	    Mat dst;

        DeltaMotor motor;
    };
}

#endif