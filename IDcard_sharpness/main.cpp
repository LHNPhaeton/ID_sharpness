#include"idcard_sharpness.h"

int main()
{
	//bool sharp;
	//Mat imageSource = imread("F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_std2\\std_sharp4.jpg");//std_sharp1
	//sharp = cal_img_sharpness(imageSource);
	//if (sharp)
	//	cout << "This image is sharp!" << endl;
	//else
	//	cout << "This image is blur!" << endl;
	
	string img_path;
	Mat img,img_blur;
	bool flag = 0;

	fstream file;
	vector<String> files;
	//string filepath = "F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_misjudge\\*jpg";
	//string filepath = "F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_IDcard\\*jpg";
	string filepath = "F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_IDgray\\*jpg"; 
	
	glob(filepath, files, true);
	int size = files.size();
	//cout << size;
	for (int i = 0; i < size; i++)
	{
	    //cout << files[i].c_str() << endl;
		img = imread(files[i].c_str(),0);
		imshow("img",img);

		flag = cal_doc_sharpness(img);
		if (flag == 1)
		{
			string img_sharp_path = "F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_sharp\\";
			img_sharp_path += to_string(i);
			img_sharp_path += ".jpg";
			//imwrite(img_sharp_path,img);
			cout << "Í¼ÏñÇåÎú" << endl;
		}
		else
		{
			string img_blur_path = "F:\\VisualStudio\\Projects\\IDcard_sharpness\\img_blur\\";
			img_blur_path += to_string(i);
			img_blur_path += ".jpg";
			//imwrite(img_blur_path, img);
			cout << "Í¼Ïñ²»ÇåÎú" << endl;
		}

		waitKey(0);
	}
	
	



	/*Mat src = imread("a.jpg");
	ID_card_cut(src);*/

	return 0;
}