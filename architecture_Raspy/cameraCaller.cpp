#include <Python.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(){

	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import picamera");
	PyRun_SimpleString("camera = picamera.PiCamera()");
	PyRun_SimpleString("camera.capture('images/image.jpg')");
	Py_Finalize();
	cv::Mat image = cv::imread("images/image.jpg");
	cv::imshow("Image", image);
	return 0;

}
