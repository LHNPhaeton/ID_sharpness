#include"idcard_sharpness.h"

bool cal_doc_sharpness(Mat img_input)
{
	/*��������ͼ��ľ�ֵ�������Ч���أ���Ч���صľ�ֵ*/
	Mat img_gray, img_OTSU;//����ͼ��ת��Ϊ�Ҷ�ͼ����������㷨���ͼ��
	int h = 0, w = 0;//ͼ��ĸߺͿ�
	double M0 = 0;
	//cout << img_input.channels;
	img_gray = img_input;
	//cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
	
	h = img_gray.size().height;
	w = img_gray.size().width;
	//cout << "h=" << h << "," << "w=" << w <<","<< "h*w=" << h*w << endl;
	//M0 = mean(img_gray)[0] * 32.0 / 255 ;
	//cout << "M0=" << M0 << endl;
	M0 = 17;
	//cout << "M0=" << M0 << endl;
	int th = threshold(img_gray, img_OTSU, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//����㷨�õ���ֵ
	
	//cout << "th=" << th*32/255 << endl;
	
	int k = 0;
	int T = 40;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (img_gray.at<unsigned char>(i, j) < th )
			{
				k++;
			}
		}
	}

	//���С����ֵth������ֵ
	double *img_temp = new double[k];
	int n = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (img_gray.at<unsigned char>(i, j) < th )
			{
				img_temp[n] = img_gray.at<unsigned char>(i, j)*32.0/255;
				n++;
			}
		}
	}
	//��img_temp�ľ�ֵ
	//cout << "img_temp=";
	double img_sum = 0;
	double M = 0;
	for (int k = 0; k < n; k++)
	{
		img_sum += img_temp[k];
		//cout << img_temp[k] << ",";
	}
	M = img_sum / n;
	//cout << "M=" << M << endl;
	
	th = th * 32 / 255;
	//cout << "th-M=" << th - M << endl;

	/*ͼ���������ж�*/
	double B = 0;
	bool sharpness = 0, sharp = 0;
	
	if (M > M0)
		B = -1;
	else
		B = 1;
	//cout << "B=" << B << endl;
	if (B == 1)
	{
		//cout << "��һ���ж�Ϊͼ������" << endl;
		if (th - M > 3.2)
		{
			sharpness = 1;
			//cout << "�ڶ����ж�Ϊͼ������" << "sharpness=" << sharpness << endl;
			sharp = cal_img_sharpness(img_input, 2.68);//2.8
			if (sharp == 0)
			{
				sharpness = 0;
				//cout << "����cal_img�����ж�Ϊͼ��ģ��" << "sharpness=" << sharpness << endl;
			}
			else if (th-M<3.26)//4
			{
				sharpness = 0;
				//cout << "�������ж�Ϊͼ��ģ��" << "sharpness=" << sharpness << endl;
			}
		}
		else
		{
			sharpness = 0;
			//cout << "�ڶ����ж�Ϊͼ��ģ��" << "sharpness=" << sharpness << endl;

			sharp = cal_img_sharpness(img_input, 3.3);
			if (sharp == 1)
			{
				sharpness = 1;
				//cout << "����cal_img�����ж�Ϊͼ������" << "sharpness=" << sharpness << endl;
			}
		}
	}
	else
	{
		//cout << "��һ���ж�Ϊͼ��ģ��" << endl;
		if (th - M > 4.3)
		{
			sharpness = 1;
			//cout << "�ڶ����ж�Ϊͼ������" << "sharpness=" << sharpness << endl;
			sharp = cal_img_sharpness(img_input, 2.5);
			if (sharp==0)
			{
				sharpness = 0;
				//cout << "����cal_img�����ж�Ϊͼ��ģ��" << "sharpness=" << sharpness << endl;
			}
		}
		else
		{
			sharpness = 0;
			//cout << "�ڶ����ж�Ϊͼ��ģ��" << "sharpness=" << sharpness << endl;
			sharp = cal_img_sharpness(img_input, 9.5);
			if (sharp)
			{
				sharpness = 1;
				//cout << "����cal_img�����ж�Ϊͼ������" << "sharpness=" << sharpness << endl;
			}
		}
	}

	//ɾ��ָ��
	delete[] img_temp;

	//waitKey(0);
	return sharpness;
}



bool cal_img_sharpness(Mat img, double std)
{
	//Mat imageSource = imread("F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_std2\\std_sharp4.jpg");//std_sharp1
	Mat imageGrey;
	bool sharp;
	imageGrey = img;
	//cvtColor(img, imageGrey, CV_RGB2GRAY);
	Mat imageSobel;
	Mat meanValueImage;
	Mat meanStdValueImage;

	//��Ҷ�ͼ��ı�׼��  
	meanStdDev(imageGrey, meanValueImage, meanStdValueImage);
	double stdValue = 0.0;
	stdValue = meanStdValueImage.at<double>(0, 0) / 3;
	//cout << "stdValue=" << stdValue << endl;


	Laplacian(imageGrey, imageSobel, CV_16U);
	//Sobel(imageGrey, imageSobel, CV_16U, 1, 1);  

	//ͼ���ƽ���Ҷ�  
	double meanValue = 0;
	meanValue = mean(imageSobel)[0];
	//cout << "LValue=" << meanValue << endl;

	//cout << "allValue=" << 0.1*stdValue + meanValue << endl;

	if (meanValue > std)
		sharp = 1;
	else
		sharp = 0;
	return sharp;
}