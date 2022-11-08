#include "opencv2/opencv.hpp"
#include "sgbm.h"
#include "test_utils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <stdio.h>

#define TEST_SGBM_LOG (1)

TEST(test_sgbm, test_normal) {
  timer start, end;

  TIME_START(start);
  TIME_END("sgbm algo", end, start);
}
