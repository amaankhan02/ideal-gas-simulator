#include <histogram.h>
#include <math.h>

using glm::vec2;
using std::string;
using std::vector;

namespace idealgas {

Histogram::Histogram(const glm::vec2& position, const glm::vec2& dimension,
                     const ci::Color& bar_color,
                     const ci::Color& axis_label_color,
                     std::string x_axis_label, std::string y_axis_label) {
  position_ = position;
  width_ = dimension[0];
  height_ = dimension[1];
  bar_color_ = bar_color;
  axis_label_color_ = axis_label_color;
  bins_ = vector<int>();
  x_axis_label_ = x_axis_label;
  y_axis_label_ = y_axis_label;
}
const ci::Color& Histogram::GetBarColor() const {
  return bar_color_;
}
const glm::vec2& Histogram::GetPosition() const {
  return position_;
}
std::string Histogram::GetXLabel() const {
  return x_axis_label_;
}
std::string Histogram::GetYLabel() const {
  return y_axis_label_;
}
void Histogram::DrawAxis() {
  ci::gl::color(axis_label_color_);
  // draw y axis
  ci::gl::drawLine(vec2(position_[0], position_[1]),
                   vec2(position_[0], position_[1] + height_));

  // draw x axis
  ci::gl::drawLine(vec2(position_[0], position_[1] + height_),
                   vec2(position_[0] + width_, position_[1] + height_));
}
void Histogram::DrawLabels() {
  ci::gl::color(axis_label_color_);
  vec2 x_label_position =
      vec2(position_[0] + (width_ / 2), position_[1] + height_ + kXLabelMargin);
  ci::gl::drawStringCentered(x_axis_label_, x_label_position, axis_label_color_,
                             ci::Font("Arial", 20));

  //  ci::rotate(-M_PI/2);
  vec2 y_label_position =
      vec2(position_[0] - kYLabelMargin, position_[1] + (height_ / 2));
  ci::gl::drawString(y_axis_label_, y_label_position, axis_label_color_,
                     ci::Font("Arial", 20));
}
void Histogram::DrawBars() {
  if (bins_.empty()) {
    return;
  }

  // find max frequency to find how much each y axis data point should go up by
  int max_freq = 0;
  for (const auto& frequency : bins_) {
    max_freq = std::max(static_cast<int>(frequency), max_freq);
  }

  float y_step =
      height_ / max_freq;  // number of pixels per one frequency value
  float bottom_y = position_[1] + height_;  // bottom y coord of the bar
  float left_x = position_[0];  // increments by bar width for each iteration

  ci::gl::color(bar_color_);
  for (const auto& value : bins_) {
    float top_y = (position_[1] + height_) - (y_step * value);
    ci::gl::drawSolidRect(
        ci::Rectf(vec2(left_x, top_y), vec2(left_x + bar_width_, bottom_y)));
    left_x += bar_width_;
  }
}
void Histogram::UpdateData(std::vector<float> data, int num_bins) {
  // clear out previous data entry
  bins_.clear();

  if (data.empty()) {
    return;
  }

  // sort in ascending order
  std::sort(data.begin(), data.end());

  float range = data[data.size() - 1] - data[0];  // max - min
  float bin_size = range / static_cast<float>(num_bins);
  bar_width_ =
      width_ / static_cast<float>(num_bins);  // pixel width of each bar

  float bin_min = data[0];             // (inclusive)
  float bin_max = bin_min + bin_size;  // (exclusive)

  // count frequencies in data and add to bin collection
  bins_.push_back(0);  // add 0 for first value
  for (float value : data) {
    if (value >= bin_max) {  // transition to new bin if necessary
      bin_min = bin_max;
      bin_max = bin_min + bin_size;
      bins_.push_back(0);
    }
    if (value >= bin_min && value < bin_max) {  // increment freq in bin
      bins_[bins_.size() - 1] = bins_[bins_.size() - 1] + 1;
    }
  }
}
void Histogram::Draw() {
  DrawBars();
  DrawAxis();
  DrawLabels();
}
float Histogram::GetBarWidth() const {
  return bar_width_;
}
const std::vector<int>& Histogram::GetBins() const {
  return bins_;
}
const glm::vec2 Histogram::GetDimensions() const {
  return vec2(width_, height_);
}
const ci::Color& Histogram::GetAxisLabelColor() const {
  return axis_label_color_;
}

}  // namespace idealgas