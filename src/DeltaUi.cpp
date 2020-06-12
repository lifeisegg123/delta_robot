#include "DeltaUi.h"

namespace delta
{
    DeltaUi::DeltaUi(QWidget* parent) : QWidget(parent)
    {
        setupUi(this);
        fd = new FaceDetector;
    }
    void DeltaUi::on_getImage_clicked()
    {
        fd->getImage();
        fd->detectFace();
        Mat frame = fd->getDst();
        Mat2QImage(frame);
        QGraphicsScene* scene = new QGraphicsScene(this);
        picture->setScene(scene);
        scene->addPixmap(QPixmap::fromImage(Mat2QImage(frame)));
    }
    void DeltaUi::on_runDrawing_clicked()
    {
        Mat frame = fd->getDst();
        Mat2QImage(frame);
        QGraphicsScene* scene = new QGraphicsScene(this);
        picture->setScene(scene);
        scene->addPixmap(QPixmap::fromImage(Mat2QImage(frame)));
        fd->searchPixel();
    }
    
    QImage DeltaUi::Mat2QImage(cv::Mat const& src)
    {
        cv::Mat temp; // make the same cv::Mat
        cvtColor(src, temp,COLOR_BGR2RGB); // cvtColor Makes a copt, that what i need
        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
        dest.bits(); // enforce deep copy, see documentation 
        // of QImage::QImage ( const uchar * data, int width, int height, Format format )
        return dest;
    }
    DeltaUi::~DeltaUi()
    {
        delete fd;
    }
}
