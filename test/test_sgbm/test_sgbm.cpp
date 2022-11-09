#include "opencv2/opencv.hpp"
#include "sgbm.h"
#include "test_utils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <stdio.h>

#define TEST_SGBM_LOG (1)

void test_sgbm() {
  timer start, end;
  cv::Mat image_L = cv::imread(TEST_SGBM_FILE_IN_L, cv::IMREAD_UNCHANGED);
  cv::Mat image_R = cv::imread(TEST_SGBM_FILE_IN_R, cv::IMREAD_UNCHANGED);

  TIME_START(start);
  // do something test
  TIME_END("sgbm algo", end, start);
}

TEST(test_sgbm, test_normal) {
  // test 1
  test_sgbm();

  // test 2

  // test 3

  // test 4
}
