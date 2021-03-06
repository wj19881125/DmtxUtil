// Dmtx_Util.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/hal/interface.h>
#include <iostream>
#include <dmtx.h>

using namespace std;
using namespace cv;




int test_data_matrix_encode(string str)
{
	//std::string str = "中国_abc_DEF_123_@#$！HTTP://WWW.LIBDMTX.ORG";
	//std::string str = "GM180329 000001";
	//std::string str = "GM180329 000002";

	DmtxEncode* enc = dmtxEncodeCreate();
	assert(enc != NULL);
	int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());
	assert(ret == 1);

	int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
	int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
	int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
	fprintf(stderr, "image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);
	assert(bytesPerPixel == 1 || bytesPerPixel == 3 || bytesPerPixel == 4);

	cv::Mat mat;
	if (bytesPerPixel == 1)
		mat = cv::Mat(height, width, CV_8UC1);
	else if (bytesPerPixel == 3)
		mat = cv::Mat(height, width, CV_8UC3);
	else
		mat = cv::Mat(height, width, CV_8UC4);

	mat.data = enc->image->pxl;

	//std::string image_name = "E:/GitCode/BarCode_Test/test_images/data_matrix_encode.jpg";
	std::string image_name = str + ".png";
	cv::imwrite(image_name, mat);

	dmtxEncodeDestroy(&enc);

	return 0;
}

int main(int argc, char* argv[])
{/*
 Mat img = imread("ic_launcher.png");

 if (img.empty())
 {
 cout << "error";
 return -1;
 }

 imshow("lena", img);*/
	//if (argc == 2)
	//{
	//	printf("The argument supplied is %s\n", argv[1]);
	//}
	//else {
	//	return 0;
	//}
	//string str = argv[1];
	std::string str = "GM180329 000001";
	test_data_matrix_encode(str);
	waitKey();

	return 0;
}

