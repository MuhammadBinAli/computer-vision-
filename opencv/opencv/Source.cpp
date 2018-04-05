// ImageSubtractionCpp.sln
// main.cpp
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>
#include "opencv2/opencv.hpp"
#include<iostream>
#include<conio.h>           
#include<fstream>
using namespace std;
using namespace cv;

int a;
double cor[4];
void finder(Mat,string);


///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	
	   
	string p = "3.jpg";
	Mat img = imread(p);
	vector<std::vector< Point> > contours;
		finder(img, "cars.xml");

	
	Rect box;
	box.width =cor[0] * 8.0;
	box.height = cor[1] * 8.0;
	box.x = cor[2] * 8.68;
	box.y = cor[3] * 8.68;
	img = imread(p, 1);
	Mat car(img, box);
	resize(car, car, Size(600, 400));
	imshow("frame",car);
	
	box.width = cor[0] *3.2;
	box.height = cor[1] * 1.4;
	box.x = cor[2] *10.32;
	box.y = cor[3] * 13.65;
	Mat crop(img, box);
	resize(crop, crop, Size(600, 400));
	finder(crop, "number plate.xml");
	box.width = cor[0] ;
	box.height = cor[1] ;
	box.x = cor[2] ;
	box.y = cor[3] ;
	Mat NP(crop, box);
	resize(NP, NP, Size(500, 250));
	imshow("frame1", NP);
	
	
	Mat NPC = NP;


	resize(NPC, NPC, Size(500, 250));
	box.width = 128;
	box.height = 250;
	box.x = 0;
	box.y = 0;
	rectangle(NPC, box, 256, CV_FILLED);
	box.width = 110;
	box.height = 250;
	box.x = 390;
	box.y = 0;
	rectangle(NPC, box, 256, CV_FILLED);
	 imshow("NPc1", NPC);
	cvtColor(NPC, NPC, CV_BGR2GRAY);
	GaussianBlur(NPC, NPC, Size(5, 5), 0);
	// adaptiveThreshold(NPC, NPC,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,11,0.5);
	adaptiveThreshold(NPC, NPC, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 0.65);
	// adaptiveThreshold(NPC, NPC, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 0.5););

	box.width = 132;
	box.height = 250;
	box.x = 0;
	box.y = 0;
	rectangle(NPC, box, 255, CV_FILLED);
	box.width = 18;
	box.height = 250;
	box.x = 385;
	box.y = 0;
	rectangle(NPC, box, 255, CV_FILLED);
	box.width = 500;
	box.height = 35;
	box.x = 0;
	box.y = 0;
	rectangle(NPC, box, 255, CV_FILLED);
	box.width = 500;
	box.height = 40;
	box.x = 0;
	box.y = 225;
	rectangle(NPC, box, 255, CV_FILLED);

	imshow("NPc2", NPC);



	// Removing small blobs

	///////////////////////////////////
	Mat threshold_output;
	vector<Vec4i> hierarchy;
	threshold(NPC, threshold_output, NULL, 255, THRESH_OTSU);
	/// Find contours
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	/// Approximate contours
	vector<Rect> boundRect(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
	{   //identify bounding box
		boundRect[i] = boundingRect(contours[i]);
	}
	for (unsigned int i = 0; i < contours.size(); i++)
	{

		if ((boundRect[i].area() < 1000))
		{
			NPC(boundRect[i]) = 256;
		}
	}
	imshow("NPc", NPC);

	///////////////////////////////////
	Mat structuringElementE = getStructuringElement(MORPH_RECT, Size(4, 7));
	Mat structuringElementD = getStructuringElement(MORPH_RECT, Size(4, 4));
	erode(NPC, NPC, structuringElementE);
	dilate(crop, crop, structuringElementD);
	structuringElementE = getStructuringElement(MORPH_RECT, Size(2, 2));
//	erode(NPC, NPC, structuringElementE);
	//  resize(NPC, NPC, Size(700, 600));
	imshow("RESULT", NPC);

	


	// Calling tesseract.exe file to read the img


	imwrite("image.jpg", NPC);
	system("tesseract.exe image.jpg out");
	system("cls");
	ifstream myReadFile;
	myReadFile.open("out.txt");
	char output[100];
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {


			myReadFile >> output;

			cout << output;


		}
	}
	myReadFile.close();



	waitKey(0);

	   return 0;
}


void finder(Mat im, string cass)
{
	Mat img = im;
	resize(img, img, Size(600, 400));
	// Load cascate classifier placed in sulution folder
	CascadeClassifier detector;
	string cascadeName = cass;
	bool loaded = detector.load(cascadeName);
	// Parameters of detectMultiscale Cascade Classifier
	int groundThreshold = 2;
	double scaleStep = 1.1;
	Size minimalObjectSize(100, 100);
	Size maximalObjectSize(200, 200);
	// Vector of returned found
	vector<Rect> found;
	// Convert input to greyscale 
	Mat image_grey;
	cvtColor(img, image_grey, CV_BGR2GRAY);
	// why not
	found.clear();
	// Detect found
	detector.detectMultiScale(image_grey, found, scaleStep, groundThreshold, 0 | 2, minimalObjectSize, maximalObjectSize);
	// Draw circles on the detected found
	for (int i = 0; i < found.size(); i++)
	{
		Point pt1(found[i].x, found[i].y); // Display detected faces on main window - live stream from camera
		Point pt2((found[i].x + found[i].height), (found[i].y + found[i].width));
		//rectangle(img, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
		a = i;

		imshow("frame0", img);
		//waitKey(0);
	}
	
	
	cor[0] = (found[a].width);
	cor[1] = (found[a].height);
	cor[2] = (found[a].x);
	cor[3] = (found[a].y);
	
	
}



