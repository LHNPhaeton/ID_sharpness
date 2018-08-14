#include"idcard_sharpness.h"

//
bool cal_doc_sharpness(Mat img_input, Mat img_blur_std)
{
	/*��������ͼ��ľ�ֵ�������Ч���أ���Ч���صľ�ֵ*/
	Mat img_gray, img_OTSU;//����ͼ��ת��Ϊ�Ҷ�ͼ����������㷨���ͼ��
	int h = 0, w = 0;//ͼ��ĸߺͿ�
	double M0;

	//cvtColor(img_input, img_gray, COLOR_BGR2GRAY);

	//imshow("ԭͼ", img_input);
	//imshow("�Ҷ�ͼ", img_gray);
	h = img_input.size().height;
	w = img_input.size().width;
	//cout << "h=" << h << "," << "w=" << w <<","<< "h*w=" << h*w << endl;
	M0 = mean(img_input)[0] * 32.0 / 255 - 3.5;
	//cout << "M0=" << M0 << endl;

	int th = threshold(img_input, img_OTSU, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//����㷨�õ���ֵ
	//imshow("����㷨", img_OTSU);
	//cout << "th=" << th << endl;

	int k = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (img_input.at<unsigned char>(i, j) < th)
			{
				k++;
			}
		}
	}
	//cout << "k=" << k << endl;

	//���С����ֵth������ֵ
	double *img_temp = new double[k];
	int n = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (img_input.at<unsigned char>(i, j) < th)
			{
				img_temp[n] = img_input.at<unsigned char>(i, j)*32.0 / 200;
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

	/*��ñ�׼ģ��ͼ��������ͼ��������ϵ���ļ���*/
	//Mat img_blur;
	//Mat img_blur_gray;
	int h_blur, w_blur;

	//img_blur = imread("25.jpg");

	//cvtColor(img_blur_std, img_blur_gray, COLOR_BGR2GRAY);
	h_blur = img_blur_std.size().height;
	w_blur = img_blur_std.size().width;
	//imshow("��׼ģ��ͼ��", img_blur);
	//imshow("��׼�Ҷ�ģ��ͼ��", img_blur_gray);

	//���ģ��ͼ�����Ч���غ���Ч���صĸ���
	int k_blur = 0;
	for (int i = 0; i < h_blur; i++)
	{
		for (int j = 0; j < w_blur; j++)
		{
			if (img_blur_std.at<unsigned char>(i, j) < 200)
			{
				k_blur++;
			}
		}
	}
	//cout << "k_blur=" << k_blur << endl;

	double *img_blur_temp = new double[k_blur];
	int n_blur = 0;
	for (int i = 0; i < h_blur; i++)
	{
		for (int j = 0; j < w_blur; j++)
		{
			if (img_blur_std.at<unsigned char>(i, j) < 200)
			{
				img_blur_temp[n_blur] = img_blur_std.at<unsigned char>(i, j)*32.0 / 255;
				n_blur++;
			}
		}
	}

	/*��������ͼ����Ч���غͱ�׼ģ��ͼ����Ч����֮������ϵ��*/
	double coef = 0, num = 0;
	double x_ = 0, y_ = 0;
	double sum1 = 0, sum2 = 0;
	num = min(k, k_blur);
	//cout << "num=" << num << endl;
	for (int i = 0; i < num; i++)
	{
		sum1 += img_temp[i];
		sum2 += img_blur_temp[i];
	}
	//cout << "sum1=" << sum1 << endl;
	//cout << "sum2=" << sum2 << endl;
	x_ = sum1 / num;
	y_ = sum2 / num;
	//cout << "x_=" << x_ << endl;
	//cout << "y_=" << y_ << endl;
	double cov = 0, var_x = 0, var_y = 0;
	for (int i = 0; i < num; i++)
	{
		cov += (img_temp[i] - x_)*(img_blur_temp[i] - y_);
		var_x += pow((img_temp[i] - x_), 2);
		var_y += pow((img_blur_temp[i] - y_), 2);
	}
	//cout << "var_x=" << var_x << endl;
	//cout << "var_y=" << var_y << endl;
	coef = cov / (sqrt(var_x*var_y));
	//cout << "coef=" << coef << endl;


	/*ͼ���������ж�*/
	double B = 0;
	bool sharpness = 0;
	int E = 4, E0 = 1;//�˴�Ϊ��ֵ�����Ǿ�����pythons�ϵĲ���֮�󣬷���E��ֵ���Ǵ���E0,���Դ˴����Լ�������һ��E=4��ֵ
	if ((E<E0) && (M <= M0))
		B = -1;
	else if ((E >= E0) && (M <= M0))
		B = coef;
	else
		B = 1;
	//cout << "B=" << B << endl;
	if (B <= 0)
	{
		sharpness = 1;
		//cout << "ͼ������" << "sharpness=" << sharpness << endl;
	}
	else
	{
		sharpness = 0;
		//cout << "ͼ��ģ��" << "sharpness=" << sharpness << endl;
	}

	//ɾ��ָ��
	delete[] img_temp;
	delete[] img_blur_temp;
	//waitKey(0);
	return sharpness;
}