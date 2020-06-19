#include "face_detection.h"
#include <unistd.h>
namespace delta
{
    FaceDetector::FaceDetector(const int cam_number) : cap(cam_number)
    {
	    cap.set(3, 320);
	    cap.set(4, 240);
		init();
    }
	int FaceDetector::init()
	{
		if (!cap.isOpened())
        {
            cerr << "Camera open failed!" << endl;
            return -1;
        }

        net = readNet(model, config);

        if (net.empty())
        {
            cerr << "Net open failed!" << endl;
            return -1;
        }
	}
    int FaceDetector::getImage()
    {
        cap >> frame;
		if (frame.empty())
        {
			return -1;
        }
    }
    void FaceDetector::detectFace()
    {
        Mat blob = blobFromImage(frame, 1, Size(300, 300), Scalar(104, 177, 123));
		net.setInput(blob);
		Mat res = net.forward();
		Mat detect(res.size[2], res.size[3], CV_32FC1, res.ptr<float>());
		for (int i = 0; i < detect.rows; i++)
        {
			float confidence = detect.at<float>(i, 2);
			if (confidence > 0.5)
			{

				int x1 = cvRound(detect.at<float>(i, 3) * frame.cols - 15);
				int y1 = cvRound(detect.at<float>(i, 4) * frame.rows - 15);
				int x2 = cvRound(detect.at<float>(i, 5) * frame.cols + 15);
				int y2 = cvRound(detect.at<float>(i, 6) * frame.rows + 15);
				
				if (x1 <= 0)
				{
					x1 = 0;
				}
				if (x2 > frame.cols)
				{
					x2 = frame.cols;
				}
				
				if (y1 <= 0)
				{
					y1 = 0;
				}
				
				if (y2 > frame.rows)
				{
					y2 = frame.rows;
				}
				faceRect = Rect(Point(x1, y1), Point(x2, y2));

				getEdges();
				putLabel(confidence, x1, y1);
				break;
			}

    	}
	}
    void FaceDetector::getEdges()
    {
        face = frame(faceRect);
        cvtColor(face, dst, COLOR_BGR2GRAY);
		GaussianBlur(dst, dst, Size(3, 3), 9);

        Canny(dst, dst, 60, 120);
		//morphologyEx(dst, dst, MORPH_GRADIENT, getStructuringElement(MORPH_CROSS, Size(3, 3)));
		
    }
    void FaceDetector::putLabel(const float &confidence, const int &x, const int &y)
    {
        rectangle(frame, faceRect, Scalar(0, 255, 0));
        //String label = format("Face: %4.3f", confidence);
        //putText(frame, label, Point(x, y+30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 0));

    }
	void FaceDetector::searchPixel()
	{
		motor.set2Zero();
		for (int j = 0; j < face.rows; j++)
		{
			uchar* p = dst.ptr<uchar>(j);
			for (int k = 0; k < face.cols; k++)
			{
				if ((int)p[k] == 255)
				{
					p[k] = 0;
					int row_c = j;
					int col_c = k;
			
					
					bool endwhile = true;
					int counter = 1;
					while(endwhile)
					{
						bool endflag = false;
						for (int row = -2; row < 3; row++)
						{
							for (int col = -2; col < 3; col++)
							{
								int row_t = row_c + row, col_t = col_c + col;

								if (row_t < 0)
								{
									row_t = 0;
								}
								else if (row_t > dst.rows)
								{
									row_t = dst.rows;
								}
								if (col_t < 0)
								{
									col_t = 0;
								}
								else if (col_t > dst.cols)
								{
									col_t = dst.cols;
								}

								uchar* new_p = dst.ptr<uchar>(row_t, col_t);
								if ((int)*new_p == 255)
								{
									endflag = true;
									row_c += row;
									col_c += col;
									if(++counter == 3)
									{
										motor.setMotorXYZ(row_c - face.rows / 2, col_c - face.cols / 2, Z_UP);
										motor.moveMotor();
										usleep(500000);
									}
									if(counter >= 3)
									{
										motor.setMotorXYZ(row_c - face.rows / 2, col_c - face.cols / 2, Z_UP);
										motor.moveMotor();
										motor.setMotorXYZ(row_c - face.rows / 2, col_c - face.cols / 2, Z_DOWN);
										motor.moveMotor();
										motor.setMotorXYZ(row_c - face.rows / 2, col_c - face.cols / 2, Z_UP);
										motor.moveMotor();
										
										*new_p = 0;
										break;
									}
								}
							}
							if (endflag)
							{
								break;
							}
						}
						endwhile = endflag;
					}
					usleep(500000);
					motor.setMotorXYZ(row_c - face.rows / 2, col_c - face.cols / 2, Z_UP);
					motor.moveMotor();
					usleep(500000);
					//motor.setMotorXYZ(0, 0, Z_UP);
					//motor.moveMotor();
					/*imshow("dst", dst);
					while(waitKey() == 27)
					{}*/
				}
			}
		}
		motor.set2Zero();
	}
	int FaceDetector::showImages()
	{
		imshow("face", dst);
		imshow("src", frame);
		if (waitKey(1) == 27)
			return 0;
	}
	Mat FaceDetector::getFrame()const
	{
		return frame;
	}
	Mat FaceDetector::getDst()const
	{
		return dst;
	}
}
