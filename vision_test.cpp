#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);
	cap.set(3, 640);
	cap.set(4, 480);
	Mat src, blur, edge;
	

	while(true)
	{
		cap >> src;

		cvtColor(src, src, COLOR_BGR2GRAY);
		//GaussianBlur(src, blur, Size(3, 3), 9);
		Canny(src, edge, 60, 120);
		imshow("src", src);
		//imshow("blur", blur);
		imshow("edge", edge);
		if (waitKey(27) == 0)
		{
			break;
		}
	}
}