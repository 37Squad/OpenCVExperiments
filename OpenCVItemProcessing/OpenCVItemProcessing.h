#pragma once

#include <string>

#include "Helper.h"

#include <opencv2\opencv.hpp>

using namespace cv;

class OpenCVItemProcessing
{
public:

	//Run application
	//Called in Main.cpp
	static int Run(int argc,char** argv);

private:

	//Image
	static cv::Mat videoImage;
	//Name of our OpenCV Window
	static std::string windowName;
	//Camera object
	static cv::VideoCapture camera;
	//Camera idx
	static int cameraIdx;


	static void ImageProcess_ColorMask(Mat);

	//Called on Startup
	static  bool Startup();
	//Cleanup time!
	static  void Cleanup();
	//Update Loop
	static bool Loop();
};

