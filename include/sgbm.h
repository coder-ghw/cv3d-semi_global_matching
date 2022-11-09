#ifndef INCLUDED_SGBM_H
#define INCLUDED_SGBM_H

#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <vector>

class SemiGlobalMatching {
public:
  SemiGlobalMatching();
  ~SemiGlobalMatching();

  enum CensusSize { Census5x5 = 0, Census9x7 };

  // SGM参数结构体
  struct SGMOption {
    uint8_t num_paths; // 聚合路径数 4 and 8
    int min_disparity;
    int max_disparity;

    CensusSize census_size; // census窗口尺寸

    bool is_check_unique; // 是否检查唯一性
    float uniqueness_ratio; // 唯一性约束阈值 （最小代价-次最小代价)/最小代价 >
                            // 阈值 为有效像素

    bool is_check_lr;    // 是否检查左右一致性
    float lrcheck_thres; // 左右一致性约束阈值

    bool is_remove_speckles; // 是否移除小的连通区
    int min_speckle_aera;    // 最小的连通区面积（像素数）

    bool is_fill_holes; // 是否填充视差空洞

    // P1,P2
    // P2 = P2_init / (Ip-Iq)
    int p1;      // 惩罚项参数P1
    int p2_init; // 惩罚项参数P2

    SGMOption()
        : num_paths(8), min_disparity(0), max_disparity(64),
          census_size(Census5x5), is_check_unique(true),
          uniqueness_ratio(0.95f), is_check_lr(true), lrcheck_thres(1.0f),
          is_remove_speckles(true), min_speckle_aera(20), is_fill_holes(true),
          p1(10), p2_init(150) {}
  };

public:
  /**
   * \brief 类的初始化，完成一些内存的预分配、参数的预设置等
   * \param width  image width
   * \param height image height
   * \param option parameters
   */
  bool Initialize(const int &width, const int &height, const SGMOption &option);

  /**
   * \brief ִmatch
   * \param [inout] disp_left left image disparity
   * \param [in] img_left	image left
   * \param [in] img_right image right
   */
  bool Match(float *disp_left, const uint8_t *img_left,
             const uint8_t *img_right);

  /**
   * \brief reset
   * \param width		image width
   * \param height	image height
   * \param option	params
   */
  bool Reset(const int &width, const int &height, const SGMOption &option);

private:
  /** \brief Census 变换 */
  void CensusTransform() const;

  /** \brief 代价计算*/
  void ComputeCost() const;

  /** \brief 代价聚合	 */
  void CostAggregation() const;

  /** \brief 视差计算	 */
  void ComputeDisparity() const;

  /** \brief 视差计算	 */
  void ComputeDisparityRight() const;

  /** \brief 一致性检查	 */
  void LRCheck();

  /** \brief 视差图像填充 */
  void FillHolesInDispMap();

  /** \brief 内存释放	 */
  void Release();

private:
  /** \brief sgm params	 */
  SGMOption option_;

  int width_;
  int height_;

  const uint8_t *img_left_;

  const uint8_t *img_right_;

  void *census_left_;
  void *census_right_;

  uint8_t *cost_init_;  //初始匹配代价
  uint16_t *cost_aggr_; //聚合匹配代价

  //聚合匹配代价 - 方向
  // ↘ ↓ ↙   5  3  7
  // →    ←	 1     2
  // ↗ ↑ ↖   8  4  6
  uint8_t *cost_aggr_1_;
  uint8_t *cost_aggr_2_;
  uint8_t *cost_aggr_3_;
  uint8_t *cost_aggr_4_;
  uint8_t *cost_aggr_5_;
  uint8_t *cost_aggr_6_;
  uint8_t *cost_aggr_7_;
  uint8_t *cost_aggr_8_;

  float *disp_left_;
  float *disp_right_;

  bool is_initialized_;                         //是否初始化标志
  std::vector<std::pair<int, int>> occlusions_; //遮挡区像素集
  std::vector<std::pair<int, int>> mismatches_; //误匹配区像素集
};

#endif
