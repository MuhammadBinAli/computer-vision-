#include "CaptureVideo.h"

#include"opencv2\opencv.hpp"

#include "opencv\cv.h"

// Capture.cpp : main project file.


#include "CaptureVideo.h"

using namespace Capture1;

[STAThreadAttribute]
int main()
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
