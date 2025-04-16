#ifndef TAGDETECTOR_H
#define TAGDETECTOR_H

#include <vector>

#include "opencv2/opencv.hpp"

#include "TagDetection.h"
#include "TagFamily.h"
#include "FloatImage.h"

#ifdef WIN32
#define _EXPORT_ __declspec(dllexport)
#else
#define _EXPORT_ __attribute__((visibility("default")))
#endif
namespace AprilTags {

class _EXPORT_ TagDetector {
public:
	
	const TagFamily thisTagFamily;

	//! Constructor
  // note: TagFamily is instantiated here from TagCodes
	 TagDetector(const TagCodes& tagCodes, const size_t blackBorder=2) : thisTagFamily(tagCodes, blackBorder) {}
	
	std::vector<TagDetection> extractTags(const cv::Mat& im);
	
};

} // namespace

#endif
