#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>

static int read_bin(const char file_path[], void *buffer, size_t size) {
  FILE *fp;
  fp = fopen(file_path, "rb");
  if (fp == NULL) {
    return -1;
  }
  fseek(fp, 0, SEEK_SET);
  size_t sz = fread(buffer, size, 1, fp);
  if (sz == 0)
    return -1;
  fclose(fp);
  return 0;
}

static int get_bin_size(const char file_path[], size_t *p_size) {
  int rc = 0;
  printf("%s:>()%s\n", __func__, rc == 0 ? "OK" : "ERROR");
  FILE *fp;
  size_t size;
  fp = fopen(file_path, "rb");
  if (fp == NULL) {
    printf("%s:fopen failed!\n", __func__);
    return -1;
  }
  fseek(fp, 0, SEEK_END); // seek to end of file
  size = ftell(fp);
  *p_size = size;
  printf("%s:|(*p_size=%lu)\n", __func__, *p_size);
  fseek(fp, 0, SEEK_SET);
  fclose(fp);
  printf("%s:<()%s\n", __func__, rc == 0 ? "OK" : "ERROR");
  return rc;
}

uint8_t *create_bin_from_file(const char *file_path, size_t *size) {
  uint8_t *buffer;
  get_bin_size(file_path, size);
  buffer = (uint8_t *)malloc(*size);
  read_bin(file_path, buffer, *size);
  return buffer;
}

int save_bin(const char *file_path, const uint8_t *buffer, size_t size) {
  FILE *fp;
  fp = fopen(file_path, "wb+");
  if (fp == NULL) {
    return -1;
  }
  printf("Writen %zu bytes to file %s\n", fwrite(buffer, 1, size, fp),
         file_path);
  fclose(fp);
  return 0;
}

void image_random_uint8(uint8_t *src, int rows, int cols, int value) {
  std::random_device rd;
  std::mt19937 engine{rd()};
  std::uniform_int_distribution<int> dist{0, value};
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      src[r * cols + c] = dist(engine);
    }
  }
}
