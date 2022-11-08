#ifndef INCLUDED_IMAGE_UTILS_H
#define INCLUDED_IMAGE_UTILS_H

#include "opencv2/opencv.hpp"
#include <string>

using namespace std;

void algo_trace_prepare(const char *debug_file);

void algo_trace(cv::Mat &img, string trace_name);

#endif
