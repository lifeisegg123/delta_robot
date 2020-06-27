#pragma once
#include "Uibase.h"
#include <QWidget>
#include <QMessageBox>
#include "face_detection.h"
namespace delta {
    class DeltaUi: public QWidget, public Ui_DeltaUi
    {
    Q_OBJECT
    public:
        DeltaUi(QWidget* parent = nullptr);
        QImage Mat2QImage(cv::Mat const& src);
        ~DeltaUi();
    public slots:
        void on_getImage_clicked();
        void on_runDrawing_clicked();
    private:
        FaceDetector* fd;
    };
}