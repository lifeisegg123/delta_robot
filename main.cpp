#include "face_detection.h"

int main() 
{
    delta::FaceDetector *fd = new delta::FaceDetector();
    fd->init();
    delete fd;
}