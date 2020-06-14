#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);
	cap.set(3, 320);
	cap.set(4, 240);
	Mat src, mid, cent, dst;
	
	Mat blurred;

	while(true)
	{
		cap >> src;

		cvtColor(src, src, COLOR_BGR2GRAY);
		equalizeHist(src, mid);
		GaussianBlur(mid, blurred, Size(3, 3), 5);
		mid = (1 + 0.8) * src - 0.8 * blurred;
		//GaussianBlur(mid, blurred, Size(5, 5), 7);
		
		/*
		String desc = format("sigma : %d", 7);
		putText(src , desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
		*/
	
		Canny(mid, dst, 200, 255);
		//morphologyEx(dst, dst, MORPH_GRADIENT, getStructuringElement(MORPH_CROSS, Size(3, 3)));
	

		imshow("src", src);
		imshow("mid", mid);
		imshow("dst", dst);
		if (waitKey(27) == 0)
		{
			break;
		}
	}
}