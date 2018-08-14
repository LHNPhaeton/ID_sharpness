#ifndef _IDCARD_SHARPNESS_H_
#define _IDCARD_SHARPNESS_H_

#include"opencv2/opencv.hpp"
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 
#include"string"
#include"iostream"
#include"cmath"
#include"vector"
using namespace cv;
using namespace std;

bool cal_doc_sharpness(Mat img_input);
bool cal_img_sharpness(Mat img, double std);

#endif