#include "image_utils.h"
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

string g_trace_folder;

/************************ static function ******************************/
static inline void getfilepath(const char *path, const char *filename,
                               char *filepath) {
  strcpy(filepath, path);
  if (filepath[strlen(path) - 1] != '/')
    strcat(filepath, "/");
  strcat(filepath, filename);
  printf("path is = %s\n", filepath);
}

static inline bool deleteFile(const char *path) {
  DIR *dir;
  struct dirent *dirinfo;
  struct stat statbuf;
  char filepath[256] = {0};
  lstat(path, &statbuf);
  if (S_ISREG(statbuf.st_mode)) //判断是否是常规文件
  {
    remove(path);
  } else if (S_ISDIR(statbuf.st_mode)) //判断是否是目录
  {
    if ((dir = opendir(path)) == NULL)
      return 1;
    while ((dirinfo = readdir(dir)) != NULL) {
      getfilepath(path, dirinfo->d_name, filepath);
      if (strcmp(dirinfo->d_name, ".") == 0 ||
          strcmp(dirinfo->d_name, "..") == 0) //判断是否是特殊目录
        continue;
      deleteFile(filepath);
      rmdir(filepath);
    }
    closedir(dir);
  }
  return 0;
}

/*****************************对外接口实现******************************/
void algo_trace_prepare(const char *debug_file) {
  int status;
  deleteFile(debug_file);
  std::string command = "mkdir -p " + std::string(debug_file);
  status = system(command.c_str());
  g_trace_folder = debug_file;
  (void)status;
}

void algo_trace(cv::Mat &img, string trace_name) {
  string trace_dir;
  trace_dir = g_trace_folder + "/" + trace_name + ".png";
  cv::imwrite(trace_dir, img);
}
