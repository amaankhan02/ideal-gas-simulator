#include "cinder/gl/gl.h"

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

namespace idealgas {

/**
 * Histogram to be displayed in the Gas Container.
 */
class Histogram {
 public:
  /**
   * Initializes histogram with parameters
   *
   * @param position            top left position of the histogram
   * @param dimension           <width, height> of the histogram
   * @param bar_color           color of each bar
   * @param axis_label_color    color of the axis lines and the x & y axis labels
   * @param x_axis_label        string to be displayed for the x axis label
   * @param y_axis_label        string to be displayed for the y axis label
   */
  Histogram(const glm::vec2& position, const glm::vec2& dimension,
            const ci::Color& bar_color, const ci::Color& axis_label_color,
            std::string& x_axis_label, std::string& y_axis_label);

  /**
   * Update the histogram with new data points. Calculates the new
   * frequencies based off the data provided and calculates the width that
   * each bar should be depending on the value of num_bins
   *
   * @param data        vector of data that you wish to find frequencies of
   * @param num_bins    number of bars/bins to be used to group data into to find
   *                    frequencies of data values that lie within each interval,
   *                    which is found using the number of bins and the range
   *                    of the data
   */
  void UpdateData(std::vector<float> data, int num_bins);

  /**
   * Draw histogram to cinder canvas
   */
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
