#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include <random>
#include <stdint.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t *create_bin_from_file(const char *file_path, size_t *size);

int save_bin(const char *file_path, const uint8_t *buffer, size_t size);

void image_random_uint8(uint8_t *src, int rows, int cols, int value);

#ifdef __cplusplus
}
#endif

#endif // !_TEST
