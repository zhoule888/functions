#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
//#include <cuda_provider_factory.h>
#include <onnxruntime_cxx_api.h>

using namespace cv;
using namespace std;
using namespace Ort;


class Informative_Drawings
{
public:
	Informative_Drawings(string modelpath);
	Mat detect(Mat& cv_image);
private:
	vector<float> input_image_;
	int inpWidth;
	int inpHeight;
	int outWidth;
	int outHeight;

	Env env = Env(ORT_LOGGING_LEVEL_ERROR, "Informative Drawings");
	Ort::Session *ort_session = nullptr;
	SessionOptions sessionOptions = SessionOptions();
	vector<char*> input_names;
	vector<char*> output_names;
	vector<string> input_names_str;
	vector<string> output_names_str;
	vector<vector<int64_t>> input_node_dims; // >=1 outputs
	vector<vector<int64_t>> output_node_dims; // >=1 outputs
};

Informative_Drawings::Informative_Drawings(string model_path)
{
	sessionOptions.SetGraphOptimizationLevel(ORT_ENABLE_BASIC);
#if defined(WIN32)
	std::wstring widestr = std::wstring(model_path.begin(), model_path.end());
	//OrtStatus* status = OrtSessionOptionsAppendExecutionProvider_CUDA(sessionOptions, 0);
	ort_session = new Session(env, widestr.c_str(), sessionOptions);
#else
	ort_session = new Session(env, model_path.c_str(), sessionOptions);
#endif
	size_t numInputNodes = ort_session->GetInputCount();
	size_t numOutputNodes = ort_session->GetOutputCount();
	AllocatorWithDefaultOptions allocator;


	for (int i = 0; i < numInputNodes; i++)
	{
		auto node_name=ort_session->GetInputNameAllocated(i, allocator);
		input_names_str.push_back(string(node_name.get()));
		//input_names.push_back((char*)(input_names_str.back().c_str()));
		Ort::TypeInfo input_type_info = ort_session->GetInputTypeInfo(i);
		auto input_tensor_info = input_type_info.GetTensorTypeAndShapeInfo();
		auto input_dims = input_tensor_info.GetShape();
		input_node_dims.push_back(input_dims);
	}
	for (auto &name:input_names_str)
		input_names.push_back((char*)name.c_str());

	for (int i = 0; i < numOutputNodes; i++)
	{
		auto node_name=ort_session->GetOutputNameAllocated(i, allocator);
		output_names_str.push_back(string(node_name.get()));
		//output_names.push_back((char*)(output_names_str.back().c_str()));
		Ort::TypeInfo output_type_info = ort_session->GetOutputTypeInfo(i);
		auto output_tensor_info = output_type_info.GetTensorTypeAndShapeInfo();
		auto output_dims = output_tensor_info.GetShape();
		output_node_dims.push_back(output_dims);
	}
	for (auto &name:output_names_str)
		output_names.push_back((char*)name.c_str());

	this->inpHeight = input_node_dims[0][2];
	this->inpWidth = input_node_dims[0][3];
	this->outHeight = output_node_dims[0][2];
	this->outWidth = output_node_dims[0][3];
}

Mat Informative_Drawings::detect(Mat& srcimg)
{
	Mat dstimg;
	resize(srcimg, dstimg, Size(this->inpWidth, this->inpHeight));
	this->input_image_.resize(this->inpWidth * this->inpHeight * dstimg.channels());
	for (int c = 0; c < 3; c++)
	{
		for (int i = 0; i < this->inpHeight; i++)
		{
			for (int j = 0; j < this->inpWidth; j++)
			{
				float pix = dstimg.ptr<uchar>(i)[j * 3 + 2 - c];
				this->input_image_[c * this->inpHeight * this->inpWidth + i * this->inpWidth + j] = pix;
			}
		}
	}
	array<int64_t, 4> input_shape_{ 1, 3, this->inpHeight, this->inpWidth };

	auto allocator_info = MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
	Value input_tensor_ = Value::CreateTensor<float>(
		allocator_info, input_image_.data(),
		input_image_.size(), input_shape_.data(), input_shape_.size());

	// ��ʼ����
	vector<Value> ort_outputs = ort_session->Run(RunOptions{ nullptr }, &input_names[0], &input_tensor_, 1, output_names.data(), output_names.size());   // ��ʼ����
	float* pred = ort_outputs[0].GetTensorMutableData<float>();
	Mat result(outHeight, outWidth, CV_32FC1, pred);
	result *= 255;
	result.convertTo(result, CV_8UC1);
	resize(result, result, Size(srcimg.cols, srcimg.rows));
	return result;
}

int main()
{
#ifdef WIN32
	string path = "D:/testProject/functions/informative-drawings-onnxrun-cpp-py-main/";
#else
	string path = "/media/lae/data/testProject/functions/informative-drawings-onnxrun-cpp-py-main\";
#endif

	Informative_Drawings mynet(path+"weights/anime_style_512x512.onnx");
	///choices=["weights/opensketch_style_512x512.onnx", "weights/anime_style_512x512.onnx", "weights/contour_style_512x512.onnx"]
	string imgpath = path+"images/2.jpg";
	Mat srcimg = imread(imgpath);
	Mat result = mynet.detect(srcimg);
	resize(result, result, Size(srcimg.cols, srcimg.rows));

	namedWindow("srcimg", WINDOW_NORMAL);
	imshow("srcimg", srcimg);
	static const string kWinName = "Deep learning in ONNXRuntime";
	namedWindow(kWinName, WINDOW_NORMAL);
	imshow(kWinName, result);
	waitKey(0);
	destroyAllWindows();
}