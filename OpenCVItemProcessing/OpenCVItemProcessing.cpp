#include "OpenCVItemProcessing.h"

std::string OpenCVItemProcessing::windowName	= "Video Feedback";
cv::Mat OpenCVItemProcessing::videoImage		= Mat();
cv::VideoCapture OpenCVItemProcessing::camera	= VideoCapture(0);
int OpenCVItemProcessing::cameraIdx				= 0;

static int ref0 = 1;

static int r_max = 255;
static int r_min = 0;
static int g_max = 255;
static int g_min = 0;
static int b_max = 255;
static int b_min = 0;

static int exposure = 12;

typedef cv::Point3_<uint8_t> Pixel;

int OpenCVItemProcessing::Run(int argc, char** argv)
{
	if (!Startup()) return -1;
	else
	{
		while (Loop()){}

		Cleanup();

		return 0;
	}
}

bool OpenCVItemProcessing::Startup()
{
	namedWindow(windowName, WINDOW_AUTOSIZE);
	namedWindow("Debug", WINDOW_AUTOSIZE);
	camera.set(CV_CAP_PROP_AUTO_EXPOSURE, 0);
	

	createTrackbar("Exposure", "Debug", &exposure, 12,
		[](int value, void* userdata)
		{

		},
		&ref0
		);

	createTrackbar("r_max", "Debug", &r_max, 255,
		[](int value, void* userdata)
		{

		},
		&ref0
	);

	createTrackbar("r_min", "Debug", &r_min, 255,
		[](int value, void* userdata)
		{

		},
		&ref0
		);

	createTrackbar("g_max", "Debug", &g_max, 255,
		[](int value, void* userdata)
		{

		},
		&ref0
		);

	createTrackbar("g_min", "Debug", &g_min, 255,
		[](int value, void* userdata)
		{

		},
		&ref0
		);

	createTrackbar("b_max", "Debug", &b_max, 255,
		[](int value, void* userdata)
		{

		},
		&ref0
		);

	createTrackbar("b_min", "Debug", &b_min, 255,
		[](int value, void* userdata)
		{

		},
		&ref0
		);


	return true;
}

void OpenCVItemProcessing::Cleanup()
{
	if (camera.isOpened()) camera.release();
	
}

bool OpenCVItemProcessing::Loop()
{
	char exit = waitKey(20);

	if (exit == 27) return false;
	else
	{
		if (camera.isOpened())
		{

			//camera.set(CV_CAP_PROP_EXPOSURE, (double)exposure - 11.0);	


			//Grab our image
			camera.read(videoImage);

			std::vector<Mat> videoCopy;

			split(videoImage, videoCopy);

			cvtColor(videoImage, videoImage, CV_BGR2GRAY);

			std::vector<Mat> channels;

			split(videoImage, channels);

			equalizeHist(channels[0], channels[0]);

			merge(channels, videoImage);

			cvtColor(videoImage, videoImage, CV_GRAY2BGR);

			//Make a pseudo grayscale image
			//ImageProcess_ColorMask(videoImage);
			//actually convert to grayscale
			//cvtColor(videoImage, videoImage, CV_BGR2GRAY);
			//To Binary
			//threshold(videoImage, videoImage, 25.0, 255.0, THRESH_BINARY);
			
			//Canny?
			//Canny(videoImage, videoImage, 0.0, 1.0, 3, false);
			
			//Show image on screen
			imshow(windowName, videoImage);
		}
		return true;
	}
}

//REMEMBER BGR FORMAT
void OpenCVItemProcessing::ImageProcess_ColorMask(Mat image)
{
	image.forEach<Pixel>([](Pixel& pixel,const int* position)->void
	{
		if (IN_RANGE(pixel.z, r_min, r_max) && IN_RANGE(pixel.y, g_min, g_max) && IN_RANGE(pixel.x, b_min, b_max))
		{
			pixel.x = 255;
			pixel.y = 255;
			pixel.z = 255;
		}
		else
		{
			pixel.x = 0;
			pixel.y = 0;
			pixel.z = 0;
		}
	});
}
