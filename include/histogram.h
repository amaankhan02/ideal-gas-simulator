#include "cinder/gl/gl.h"

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

namespace idealgas {

/**
 * Represents a Histogram to be displayed in the Gas Container
 */
class Histogram {
 public:
  Histogram(glm::vec2 position, glm::vec2 dimension, ci::Color bar_color,
            ci::Color axis_color);

  void UpdateData(std::vector<float> data, int num_bins);
  void Draw();

  const glm::vec2& GetPosition() const;
  const ci::Color& GetBarColor() const;
  const ci::Color& GetAxisColor() const;
  std::string GetXLabel() const;
  std::string GetYLabel() const;

  void SetXLabel(std::string x_label);
  void SetYLabel(std::string y_label);

 private:
  glm::vec2 position_;
  float width_;
  float height_;
  ci::Color bar_color_;
  ci::Color axis_color_;
  std::string x_label_; // x-axis label
  std::string y_label_; // y-axis label
  float bar_width_;     // width of each bar in the graph

  /**
   * vector of frequencies for each bar/bin
   */
  std::vector<int> bins_; // TODO: rename to frequencies_? instead of bins_?

  void DrawLabels();
  void DrawAxis();
  void DrawBars();

};
}

#endif  // IDEAL_GAS_HISTOGRAM_H
