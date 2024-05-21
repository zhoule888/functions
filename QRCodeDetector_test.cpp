#if 0
//Opencv QRCode

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat img;
	double t = 0;
	double fps;

	img=imread("../2.jpg");
	cv::resize(img,img,cv::Size(360,640));
	cvtColor(img,img,cv::COLOR_BGR2GRAY);
	t = (double)cv::getTickCount();

	cv::QRCodeDetector QRdetecter;
	std::vector<cv::Point> list;
	cv::Mat  res;
	string str = QRdetecter.detectAndDecode(img, list, res);
	std::cout <<  "QR:" << str << std::endl;
	for (int j = 0; j < list.size(); j++)
	{
		if (j == 3)
			line(img, list[j], list[0], Scalar(0, 255, 0), 2);
		else
			line(img, list[j], list[j + 1], Scalar(0, 255, 0), 2);
	}
	namedWindow("org", 0);
	imshow("org", img);
	if (res.data)
	{
		namedWindow("二维码ROI", 0);
		imshow("二维码ROI", res);
	}
	t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
	fps = 1.0 / t;
	cout<<fps<<endl;
	waitKey(0);

	return 0;
}
#endif


#if 0
//zxing qrcode

#include <string>
#include <exception>
#include <stdlib.h>
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/MatSource.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace zxing;
using namespace zxing::qrcode;
using namespace cv;


Point toCvPoint(Ref<ResultPoint> resultPoint) {
	return Point(resultPoint->getX(), resultPoint->getY());
}

int detectQRCode(const cv::Mat imGray)
{
	cv::Mat im=imGray.clone();


	cv::Mat image;
	cv::cvtColor(im,image,cv::COLOR_GRAY2BGR);
	try{

		// Create luminance  source
		Ref<LuminanceSource> source = MatSource::create(im);

		// Search for QR code
		Ref<Reader> reader;
		//reader.reset(new QRCodeReader);
		reader.reset(new zxing::qrcode::QRCodeReader);

		Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(source));
		Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
		Ref<Result> result=reader->decode(bitmap, DecodeHints(DecodeHints::QR_CODE_HINT));
		//Ref<Result> result(reader->decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));

		// Get result point count
		int resultPointCount = result->getResultPoints()->size();



		for (int j = 0; j < resultPointCount; j++) {

			// Draw circle
			circle(image, toCvPoint(result->getResultPoints()[j]), 10, Scalar( 110, 220, 0 ), 2);

		}

		if (resultPointCount > 1) {

			for (int j = 0; j < resultPointCount; j++) {

				// Get start result point
				Ref<ResultPoint> previousResultPoint = (j > 0) ? result->getResultPoints()[j - 1] : result->getResultPoints()[resultPointCount - 1];

				// Draw line
				line(image, toCvPoint(previousResultPoint), toCvPoint(result->getResultPoints()[j]), Scalar( 110, 220, 0 ),  2, 8 );

				// Update previous point
				previousResultPoint = result->getResultPoints()[j];

			}

		}

		if (resultPointCount > 0) {

			// Draw text
			putText(image, result->getText()->getText(), toCvPoint(result->getResultPoints()[1]), FONT_HERSHEY_PLAIN, 1,
			        Scalar( 110, 220, 0 ));

		}
	}catch (const ReaderException& e) {
		cerr << e.what() << " (ignoring)" << endl;
	} catch (const zxing::IllegalArgumentException& e) {
		cerr << e.what() << " (ignoring)" << endl;
	} catch (const zxing::Exception& e) {
		cerr << e.what() << " (ignoring)" << endl;
	} catch (const std::exception& e) {
		cerr << e.what() << " (ignoring)" << endl;
	}


	imshow("ZXing", image);
	cv::waitKey();

	return 0;
}

int main()
{
	cv::Mat img=imread("../1.jpeg");
	//cv::resize(img,img,cv::Size(360,640));
	cvtColor(img,img,cv::COLOR_BGR2GRAY);

	detectQRCode(img);
	return 0;
}

#endif

#if 1

//wechat qrcode detect by opencv4.9.0
#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/wechat_qrcode.hpp>

using namespace std;
using namespace cv;
using namespace cv::wechat_qrcode;

int main()
{
	Mat src = imread("../1.jpeg");

	if (src.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	imshow("src image", src);

	Ptr<WeChatQRCode> detector;
	string detect_prototxt = "../model/detect.prototxt";
	string detect_caffe_model = "../model/detect.caffemodel";
	string sr_prototxt = "../model/sr.prototxt";
	string sr_caffe_model = "../model/sr.caffemodel";

	try
	{
		detector = makePtr< WeChatQRCode>(detect_prototxt, detect_caffe_model,
		                                  sr_prototxt, sr_caffe_model);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return -1;
	}
	vector<Mat> vPoints;
	vector<String> strDecoded;
	strDecoded = detector->detectAndDecode(src, vPoints);

	for (int i = 0; i < strDecoded.size(); i++)
	{
		cout << "decode-" << i + 1 << ": " << strDecoded[i] << endl;
		Point pt1 = Point((int)vPoints[i].at<float>(0, 0), (int)vPoints[i].at<float>(0, 1));
		Point pt2 = Point((int)vPoints[i].at<float>(1, 0), (int)vPoints[i].at<float>(1, 1));
		Point pt3 = Point((int)vPoints[i].at<float>(2, 0), (int)vPoints[i].at<float>(2, 1));
		Point pt4 = Point((int)vPoints[i].at<float>(3, 0), (int)vPoints[i].at<float>(3, 1));
		line(src, pt1, pt2, Scalar(0, 255, 0), 2);
		line(src, pt2, pt3, Scalar(0, 255, 0), 2);
		line(src, pt3, pt4, Scalar(0, 255, 0), 2);
		line(src, pt4, pt1, Scalar(0, 255, 0), 2);
		putText(src, strDecoded[i], pt1, 0, 0.5, Scalar(255, 0, 0), 2);
	}

	imshow("result image", src);


	waitKey(0);
	return 0;
}




#endif