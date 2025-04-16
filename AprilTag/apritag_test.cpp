//
// Created by lae on 24-4-16.
//
#ifdef WIN32
#include <time.h>
#include <windows.h>
#endif
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "TagDetector.h"
//#include "TagFamily.h"

#ifdef WIN32
int gettimeofday(struct timeval* tp, void* tzp) {
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#else
#include <sys/time.h>
#endif


int jcx_taglocation_detect_apriltag_points(cv::Mat image, cv::Mat image_ori,
                                           std::map<int, cv::Point2f> &pts2d,
                                           cv::Point2f &center,
                                           std::map<int,cv::Point2f> &out_points)
{
	struct timeval tv0,tv1;
	gettimeofday(&tv0, 0);

	if(image.empty())
	{
		printf("image is empty!\n");
		return -1;
	}

	if (!pts2d.empty())
		pts2d.clear();

	out_points.clear();

	cv::imshow("detectimage", image);
	cv::waitKey(1);


	std::shared_ptr<AprilTags::TagDetector> tag_detector_ptr =
			std::shared_ptr<AprilTags::TagDetector>(new AprilTags::TagDetector(AprilTags::tagCodes36h11));
	std::vector<AprilTags::TagDetection> detections = tag_detector_ptr->extractTags(image);
	if (detections.empty())
	{
		//JCX_LOGE("%s [%s:%d]: %s\n", JCX_LOG_TAG, __FILE__, __LINE__, "TAGLOCATION_FAILED_DETECTING_TAGS");
		printf("no detections!\n");
		return -1;
	}

	// min. distance form image border for valid points [px]
	double min_border_distance = 4.0;
	int min_tags = 1;

	// if do sub-pixel refine
	bool do_subpix_refinement = true;

	// min. distance [px] of tag corners from image border (tag is not used if violated)
	std::vector<AprilTags::TagDetection>::iterator iter = detections.begin();
	printf("detect %d tags!\n",detections.size());
	for (iter = detections.begin(); iter != detections.end();)
	{
		// check all four corners for violation
		bool remove = false;

		for (int j = 0; j < 4; j++)
		{
			remove |= iter->p[j].first < min_border_distance;
			remove |= iter->p[j].first > (double)(image.cols) - min_border_distance; // width
			remove |= iter->p[j].second < min_border_distance;
			remove |= iter->p[j].second > (double)(image.rows) - min_border_distance; // height
		}

		// also remove tags that are flagged as bad
		if (iter->good != 1)
			remove |= true;

		// delete flagged tags
		if (remove)
		{
			// delete the tag and advance in list
			printf("remove detections\n");
			iter = detections.erase(iter);
		}
		else
		{
			// advance in list
			++iter;
		}
	}
	printf("detections.size=%d\n",detections.size());
	if (detections.size() < min_tags)
		return -2;

	// sort detections by tagId
	std::sort(detections.begin(), detections.end(), AprilTags::TagDetection::sortByIdCompare);

	cv::Mat tag_corners(4 * detections.size(), 2, CV_32F);
	//double scale_ratio_inv = jcx_tagloc_params.is_rgb_camera_ ? 1.0 / jcx_tagloc_params.rgb_image_scale_ratio : 1.0;
	double scale_ratio_inv=1.0;
	for (int i = 0; i < detections.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tag_corners.at<float>(4 * i + j, 0) = detections[i].p[j].first * scale_ratio_inv;
			tag_corners.at<float>(4 * i + j, 1) = detections[i].p[j].second * scale_ratio_inv;
		}
	}

	// optional subpixel refinement on all tag corners (four corners each tag)
	if (do_subpix_refinement)
		cv::cornerSubPix(image_ori, tag_corners, cv::Size(2, 2), cv::Size(-1, -1),
			cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 30, 0.1));

	for (int i = 0; i < detections.size(); i++)
	{
		// get tag and vertex id
		int tag_id = detections[i].id;
		int vtx_id = 4 * tag_id;
		for (int j = 0; j < 4; j++)
		{
			pts2d.insert({vtx_id + j, cv::Point2f(tag_corners.at<float>(4 * i + j, 0), tag_corners.at<float>(4 * i + j, 1))});
		}
	}

	{
		cv::Mat image_tmp;
		cv::cvtColor(image_ori, image_tmp, cv::COLOR_GRAY2BGR);

		int i=0;
		for (auto pt= pts2d.begin(); pt != pts2d.end(); pt++,i++)
		{
			center=pt->second;
			auto tmppt = pt;
			auto pt1=pt;
			auto pt2=pt++;
			cv::line(image_tmp, pt1->second, pt2->second, cv::Scalar(0,255,0), 2);
			center+=pt2->second;
			if (pt == pts2d.end()) break;
			pt1=pt;pt2=pt++;
			cv::line(image_tmp, pt1->second, pt2->second, cv::Scalar(0,255,0), 2);
			center+=pt2->second;
			if (pt == pts2d.end()) break;
			pt1=pt;pt2=pt++;
			cv::line(image_tmp, pt1->second, pt2->second, cv::Scalar(0,255,0), 2);
			center+=pt->second;
			if (pt == pts2d.end()) break;
			cv::line(image_tmp, pt->second, tmppt->second, cv::Scalar(0,255,0), 2);

			center/=4;
			out_points.insert(std::make_pair(detections[i].id, center));
			cv::circle(image_tmp,center,2,cv::Scalar(0,0,255),2);

			cv::putText(image_tmp,std::to_string(detections[i].id),center,
						cv::FONT_HERSHEY_SIMPLEX,0.75,cv::Scalar(0,0,255),1);
		}
		cv::imshow("image_tmp",image_tmp);

		cv::waitKey(0);
	}
	gettimeofday(&tv1, 0);
	printf("time : %ld ms\n",
	       (tv1.tv_sec - tv0.tv_sec) * 1000 + (tv1.tv_usec - tv0.tv_usec) / 1000);

	return 0;
}


int detect_apriltag_points(cv::Mat image, std::map<int, cv::Point2f>& detect_points,
	const AprilTags::TagCodes& tagCodes= AprilTags::tagCodes36h11, bool show=false)
{
	if (image.empty())
	{
		printf("image is empty!\n");
		return -1;
	}

	detect_points.clear();

	std::shared_ptr<AprilTags::TagDetector> tag_detector_ptr =
		std::shared_ptr<AprilTags::TagDetector>(new AprilTags::TagDetector(tagCodes));
	std::vector<AprilTags::TagDetection> detections = tag_detector_ptr->extractTags(image);
	if (detections.empty())
	{
		//JCX_LOGE("%s [%s:%d]: %s\n", JCX_LOG_TAG, __FILE__, __LINE__, "TAGLOCATION_FAILED_DETECTING_TAGS");
		printf("no detections!\n");
		return -2;
	}

	double min_border_distance = 4.0;
	int min_tags = 1;

	// if do sub-pixel refine
	bool do_subpix_refinement = true;

	std::vector<AprilTags::TagDetection>::iterator iter = detections.begin();
	printf("detect %d tags!\n", detections.size());

	for (iter = detections.begin(); iter != detections.end();)
	{
		// check all four corners for violation
		bool remove = false;

		for (int j = 0; j < 4; j++)
		{
			remove |= iter->p[j].first < min_border_distance;
			remove |= iter->p[j].first > (double)(image.cols) - min_border_distance; // width
			remove |= iter->p[j].second < min_border_distance;
			remove |= iter->p[j].second > (double)(image.rows) - min_border_distance; // height
		}

		// also remove tags that are flagged as bad
		if (iter->good != 1)
			remove |= true;

		// delete flagged tags
		if (remove)
		{
			// delete the tag and advance in list
			printf("remove detections\n");
			iter = detections.erase(iter);
		}
		else
		{
			// advance in list
			++iter;
		}
	}

	printf("detections.size=%d\n", detections.size());
	if (detections.size() < min_tags)
		return -3;

	// sort detections by tagId
	std::sort(detections.begin(), detections.end(), AprilTags::TagDetection::sortByIdCompare);

	cv::Mat tag_corners(4 * detections.size(), 2, CV_32F);
	//double scale_ratio_inv = jcx_tagloc_params.is_rgb_camera_ ? 1.0 / jcx_tagloc_params.rgb_image_scale_ratio : 1.0;
	double scale_ratio_inv = 1.0;
	for (int i = 0; i < detections.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tag_corners.at<float>(4 * i + j, 0) = detections[i].p[j].first * scale_ratio_inv;
			tag_corners.at<float>(4 * i + j, 1) = detections[i].p[j].second * scale_ratio_inv;
		}
	}


	// optional subpixel refinement on all tag corners (four corners each tag)
	if (do_subpix_refinement)
		cv::cornerSubPix(image, tag_corners, cv::Size(2, 2), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 30, 0.1));

	std::map<int, cv::Point2f> pts2d;
	for (int i = 0; i < detections.size(); i++)
	{
		// get tag and vertex id
		int tag_id = detections[i].id;
		int vtx_id = 4 * tag_id;
		for (int j = 0; j < 4; j++)
		{
			pts2d.insert({ vtx_id + j, cv::Point2f(tag_corners.at<float>(4 * i + j, 0), tag_corners.at<float>(4 * i + j, 1)) });
		}
	}

	{
		cv::Mat image_tmp;
		cv::cvtColor(image, image_tmp, cv::COLOR_GRAY2BGR);

		cv::Point2f center(0,0);
		for (int i=0;i<detections.size();++i) {
			auto pt1=pts2d[i*4];
			auto pt2=pts2d[i*4+1];
			auto pt3=pts2d[i*4+2];
			auto pt4=pts2d[i*4+3];

			center=(pt1+pt2+pt3+pt4)/4;
			detect_points.insert(std::make_pair(detections[i].id, center));
			if(show) {
				cv::line(image_tmp, pt1, pt2, cv::Scalar(0,255,0), 2);
				cv::line(image_tmp, pt2, pt3, cv::Scalar(0,255,0), 2);
				cv::line(image_tmp, pt3, pt4, cv::Scalar(0,255,0), 2);
				cv::line(image_tmp, pt1, pt4, cv::Scalar(0,255,0), 2);

				cv::circle(image_tmp, center, 2, cv::Scalar(0, 0, 255), 2);
				cv::putText(image_tmp, std::to_string(detections[i].id), center,
					cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 255), 1);

			}


		}


		if (show)
		{
			cv::imshow("image_tmp", image_tmp);
			cv::waitKey(0);
		}
		
	}
}

int main()
{
	//cv::VideoCapture cap(0,cv::CAP_DSHOW);
	//if(cap.isOpened())
	//{
	//	cv::Mat frame;
	//	while(1)
	//	{
	//		cap>>frame;
	//		if(!frame.empty())
	//		{
	//			cv::imshow("frame",frame);
	//			cv::waitKey(1);
	//		}
	//	}
	//}
	//else
	//	printf("cannot open video\n");

	//return 0;


#if 1
	cv::Mat im=cv::imread("D:/testProject/functions/AprilTag/1713321723830300000.png",0);
	std::map<int, cv::Point2f> pts2d;
	cv::Point2f center;
	detect_apriltag_points(im,pts2d, AprilTags::tagCodes36h11,true);
#else
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cerr << "Error opening video file\n";
		return -1;
	}
	cv::Mat frame;
	while(1)
	{
		cap.read(frame);
//		frame = cv::imread("/media/lae/data/projects/mercury_steamvr_driver/cmake-build-release/src/data1/cam0/1713321719427100000.png");
		if (frame.empty())
		{
			std::cout << "End of stream\n";
			break;
		}

		cv::Mat img;
		if(frame.channels()==3)
			cv::cvtColor(frame,img,cv::COLOR_BGR2GRAY);
		else
			img=frame.clone();

		std::map<int, cv::Point2f> pts;
		cv::Point2f center;
		jcx_taglocation_detect_apriltag_points(img,img,pts,center);


	}

#endif

	return 0;
}