//
// Created by lae on 24-4-16.
//
#include "opencv2/opencv.hpp"
#include "TagDetector.h"
#include <sys/time.h>

int jcx_taglocation_detect_apriltag_points(cv::Mat image, cv::Mat image_ori,
                                           std::map<int, cv::Point2f> &pts2d,
                                           cv::Point2f &center)
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

	cv::imshow("detectimage", image);
	cv::waitKey(1);


	std::shared_ptr<AprilTags::TagDetector> tag_detector_ptr =
			std::shared_ptr<AprilTags::TagDetector>(new AprilTags::TagDetector(AprilTags::tagCodes16h5));
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
		cv::cornerSubPix(image_ori, tag_corners, cv::Size(2, 2), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 30, 0.1));

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
			cv::line(image_tmp, pt->second, (pt++)->second, cv::Scalar(0,255,0), 2);
			center+=pt->second;
			if (pt == pts2d.end()) break;
			cv::line(image_tmp, pt->second, (pt++)->second, cv::Scalar(0,255,0), 2);
			center+=pt->second;
			if (pt == pts2d.end()) break;
			cv::line(image_tmp, pt->second, (pt++)->second, cv::Scalar(0,255,0), 2);
			center+=pt->second;
			if (pt == pts2d.end()) break;
			cv::line(image_tmp, pt->second, tmppt->second, cv::Scalar(0,255,0), 2);

			center/=4;
			cv::circle(image_tmp,center,2,cv::Scalar(0,0,255),2);

			cv::putText(image_tmp,std::to_string(detections[i].id),center,
						cv::FONT_HERSHEY_SIMPLEX,0.75,cv::Scalar(0,0,255),1);
		}
		cv::imshow("image_tmp",image_tmp);

		cv::waitKey(1);
	}
	gettimeofday(&tv1, 0);
	printf("time : %ld ms\n",
	       (tv1.tv_sec - tv0.tv_sec) * 1000 + (tv1.tv_usec - tv0.tv_usec) / 1000);

	return 0;
}


int main()
{
#if 0
	cv::Mat im=cv::imread("../1.jpg",0);
	std::map<int, cv::Point2f> pts2d;
	cv::Point2f center;
	jcx_taglocation_detect_apriltag_points(im,im,pts2d,center);
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