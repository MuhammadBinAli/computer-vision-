
#include"opencv2\opencv.hpp"

#include "opencv\cv.h"

using namespace cv;


int main()
{
	VideoCapture cap(0);

	while (1)
	{
		Mat f;
		cap.read(f);
		imshow("a",f);
		waitKey(1);

	}

}