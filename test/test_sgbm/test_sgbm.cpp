#include "image_utils.h"
#include "opencv2/opencv.hpp"
#include "sgbm.h"
#include "test_utils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <opencv2/core/base.hpp>
#include <opencv2/imgcodecs.hpp>
#include <stdio.h>
#include <string>

#define TEST_SGBM_LOG (1)

void test_sgbm() {
  cv::Mat image_L_color = cv::imread(TEST_SGBM_FILE_IN_L, cv::IMREAD_UNCHANGED);
  cv::Mat image_L = cv::imread(TEST_SGBM_FILE_IN_L, cv::IMREAD_GRAYSCALE);
  cv::Mat image_R = cv::imread(TEST_SGBM_FILE_IN_R, cv::IMREAD_GRAYSCALE);
  int width = image_L.cols;
  int height = image_L.rows;
  cv::Mat image_disparity(height, width, CV_32FC1);

  // SGM匹配参数设计
  SemiGlobalMatching::SGMOption sgm_option;
  // 聚合路径数
  sgm_option.num_paths = 8;
  // 候选视差范围
  sgm_option.min_disparity = 0;
  sgm_option.max_disparity = 50;
  // census窗口类型
  sgm_option.census_size = SemiGlobalMatching::Census5x5;
  // 一致性检查
  sgm_option.is_check_lr = true;
  sgm_option.lrcheck_thres = 1.0f;
  // 唯一性约束
  sgm_option.is_check_unique = true;
  sgm_option.uniqueness_ratio = 0.99;
  // 剔除小连通区
  sgm_option.is_remove_speckles = true;
  sgm_option.min_speckle_aera = 50;
  // 惩罚项P1、P2
  sgm_option.p1 = 10;
  sgm_option.p2_init = 150;
  // 视差图填充
  // 视差图填充的结果并不可靠，若工程，不建议填充，若科研，则可填充
  sgm_option.is_fill_holes = false;

  SemiGlobalMatching sgm;

  timer start, end;
  TIME_START(start);
  if (!sgm.Initialize(width, height, sgm_option)) {
    std::cout << "SGM初始化失败..." << std::endl;
  }
  TIME_END("sgbm initialize", end, start);

  TIME_START(start);
  if (!sgm.Match((float *)image_disparity.data, image_L.data, image_R.data)) {
    std::cout << "SGM匹配失败..." << std::endl;
  }
  TIME_END("sgbm match", end, start);
  if (TEST_SGBM_LOG) {
    cv::Mat result = cv::Mat::zeros(height, width, CV_8UC1);

    cv::String file_result =
        cv::format("%s/image_disparity.png", TEST_TRACE_DIR);
    float min_disp = width, max_disp = -width;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        const float disp = image_disparity.at<float>(i, j);
        if (disp != Invalid_Float) {
          min_disp = std::min(min_disp, disp);
          max_disp = std::max(max_disp, disp);
        }
      }
    }
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        const float disp = image_disparity.at<float>(i, j);
        if (disp == Invalid_Float) {
          result.data[i * width + j] = 0;
        } else {
          result.data[i * width + j] = static_cast<uchar>(
              (disp - min_disp) / (max_disp - min_disp) * 255);
        }
      }
    }
    cv::imwrite(file_result, result);
  }
}

TEST(test_sgbm, test_normal) {
  algo_trace_prepare(TEST_TRACE_DIR);
  // test 1
  test_sgbm();

  // test 2

  // test 3

  // test 4
}
