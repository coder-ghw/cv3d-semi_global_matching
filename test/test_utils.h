#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include <chrono>
#include <random>
#include <stdint.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

inline void time_start(std::chrono::steady_clock::time_point &start) {
  start = std::chrono::steady_clock::now();
}

inline void time_end(const char *info,
                     std::chrono::steady_clock::time_point &start) {
  auto end = std::chrono::steady_clock::now();
  auto tt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  printf("\033[1;33;41m%s:use time %f ms\033[0m\n", info, tt.count() / 1.f);
}

uint8_t *create_bin_from_file(const char *file_path, size_t *size);

int save_bin(const char *file_path, const uint8_t *buffer, size_t size);

void image_random_uint8(uint8_t *src, int rows, int cols, int value);

#ifdef __cplusplus
}
#endif

#endif // !_TEST
