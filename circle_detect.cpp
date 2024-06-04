//
// Created by lae on 24-5-22.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
int main() {

	Mat src_gray,gray_image;
	Mat src = imread("../img.png");
	cvtColor( src, src_gray, COLOR_BGR2GRAY );
	GaussianBlur( src_gray , gray_image, Size(9, 9), 2, 2 );
	Canny(gray_image,gray_image ,50,100,3);
	imshow("result", gray_image);
	waitKey(1);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(gray_image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat cimage = Mat::zeros(gray_image.size(), CV_8UC3);
	cout<<"contours.size() "<<contours.size()<<endl;
	//最小外接椭圆，输入点一定大于5个
	vector<RotatedRect> box(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{

		//拟合的点至少为6
		size_t count = contours[i].size();
		if( count < 3 )
			continue;
		else
		{
			//返回包覆输入信息的最小正矩形。
			cv::Rect r = cv::boundingRect(contours[i]);

			//  cout<<"矩阵长/宽  "<<r.width <<" "<<r.height<<endl;
			//矩形长宽比
			double ratio=(double)r.height/ r.width;

			//if (ratio>=1.95 && ratio <= 3.94)
			if(ratio<1.2 && ratio>1./1.2)
			{
				//二维点集，要求拟合的点至少为6个点
				//输出：RotatedRect 类型的矩形，是拟合出椭圆的最小外接矩形
				box[i] = fitEllipse(Mat(contours[i]));

				//cout<<"椭圆长/短 "<<box[i].size.width<<" "<<box[i].size.height<<endl;
				double r=(double)box[i].size.height/box[i].size.width;
				// double ang=box[i].angle;
				double square=(double)box[i].size.height*box[i].size.width;
				//if( r >=1.8 && r<=2.3 && square >=17350 && square <=21100)
				if(ratio<1.2 && ratio>1./1.2)
				{
					cout<<"square "<<square<<endl;
					// cout<<"角度 "<<box[i].angle<<endl;
					cout<<"椭圆长/短 "<<box[i].size.width<<" "<<box[i].size.height<<endl;
					//画出追踪出的轮廓
					drawContours(cimage, contours, (int)i, Scalar::all(255), 1, 8);
					//画出拟合的椭圆
					ellipse(cimage, box[i], Scalar(0,0,255), 1, LINE_AA);
					imshow("cimage", cimage);
					waitKey(1);
					ellipse(src, box[i], Scalar(0,0,255), 1, LINE_AA);
					imshow("srccc", src);
					waitKey(0);
				}
			}
		}
	}
	return 0;
}
