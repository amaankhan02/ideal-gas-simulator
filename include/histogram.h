#include "cinder/gl/gl.h"

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

namespace idealgas {

/**
 * Represents a Histogram to be displayed in the Gas Container
 */
class Histogram {
 public:
  Histogram(const glm::vec2& position, const glm::vec2& dimension,
            const ci::Color& bar_color, const ci::Color& axis_label_color,
            std::string& x_axis_label, std::string& y_axis_label);

  void UpdateData(std::vector<float> data, int num_bins);
  void Draw();

  const glm::vec2& GetPosition() const;
  const ci::Color& GetBarColor() const;
  const ci::Color& GetAxisLabelColor() const;
  const glm::vec2 GetDimensions() const;
  std::string GetXLabel() const;
  std::string GetYLabel() const;
  float GetBarWidth() const;
  const std::vector<int>& GetBins() const;

 private:
  const float kXLabelMargin = 10;
  const float kYLabelMargin = 85;
  glm::vec2 position_;
  float width_;
  float height_;
  ci::Color bar_color_;
  ci::Color axis_label_color_;
  std::string x_axis_label_; // x-axis label
  std::string y_axis_label_; // y-axis label
  float bar_width_;     // width of each bar in the graph

  /**
   * vector of frequencies for each bar/bin
   */
  std::vector<int> bins_;

  void DrawLabels();
  void DrawAxis();
  void DrawBars();

};
}

#endif  // IDEAL_GAS_HISTOGRAM_H
