#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include <random>
#include <stdint.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct timeval timer;
#define TIME_START(start) gettimeofday(&start, 0);

#define TIME_END(info, end, start)                                             \
  gettimeofday(&end, 0);                                                       \
  time_substract(&end, &start, &end);                                          \
  printf("\033[1;33;41m%s:use time %d us\033[0m\n", info, (int)end.tv_usec);

static inline int time_substract(struct timeval *result, struct timeval *begin,
                                 struct timeval *end) {
  if (begin->tv_sec > end->tv_sec)
    return -1;
  if ((begin->tv_sec == end->tv_sec) && (begin->tv_usec > end->tv_usec))
    return -2;
  result->tv_sec = (end->tv_sec - begin->tv_sec);
  result->tv_usec = (end->tv_usec - begin->tv_usec);

  if (result->tv_usec < 0) {
    result->tv_sec--;
    result->tv_usec += 1000000;
  }
  return 0;
}

uint8_t *create_bin_from_file(const char *file_path, size_t *size);

int save_bin(const char *file_path, const uint8_t *buffer, size_t size);

void image_random_uint8(uint8_t *src, int rows, int cols, int value);

#ifdef __cplusplus
}
#endif

#endif // !_TEST
