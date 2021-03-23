#include <histogram.h>
using glm::vec2;
using std::string;
using std::vector;

namespace idealgas {

Histogram::Histogram(glm::vec2 position, glm::vec2 dimension,
                     ci::Color bar_color, ci::Color axis_color) {
  position_ = position;
  width_ = dimension[0];
  height_ = dimension[1];
  bar_color_ = bar_color;
  axis_color_ = axis_color;
  bins_ = vector<int>();
}
const ci::Color& Histogram::GetBarColor() const {
  return bar_color_;
}
const glm::vec2& Histogram::GetPosition() const {
  return position_;
}
std::string Histogram::GetXLabel() const {
  return x_label_;
}
std::string Histogram::GetYLabel() const {
  return y_label_;
}
void Histogram::SetXLabel(string x_label) {
  x_label_ = x_label;
}
void Histogram::SetYLabel(string y_label) {
  y_label_ = y_label;
}
void Histogram::DrawAxis() {
  ci::gl::color(axis_color_);
  // draw y axis
  ci::gl::drawLine(
      vec2(position_[0], position_[1]),
      vec2(position_[0], position_[1] + height_));

  // draw x axis
  ci::gl::drawLine(
      vec2(position_[0], position_[1] + height_),
      vec2(position_[0] + width_, position_[1] + height_));
}
void Histogram::DrawLabels() {

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

  float y_step = height_ / max_freq; // number of pixels per one frequency value
  float bottom_y = position_[1] + height_; // bottom y coord of the bar
  float left_x = position_[0];  // increments by bar width for each iteration

  ci::gl::color(bar_color_);
  for (const auto& value : bins_) {
    float top_y = (position_[1] + height_) - (y_step * value);
    ci::gl::drawSolidRect(ci::Rectf(vec2(left_x, top_y),
                                    vec2(left_x + bar_width_, bottom_y)));
    left_x += bar_width_;
  }
}
void Histogram::UpdateData(std::vector<float> data, int num_bins) {
  // clear out previous data entry
  bins_.clear();

  // sort in ascending order
  std::sort(data.begin(), data.end());

  float range = data[data.size() - 1] - data[0]; // max - min
  float bin_size = range / static_cast<float>(num_bins);
//  int num_bins = static_cast<int>(ceil(range / bin_size)); // num of bins to display
  bar_width_ = width_ / static_cast<float>(num_bins); // pixel width of each bar

  float bin_min = data[0];            // (inclusive)
  float bin_max = bin_min + bin_size; // (exclusive)
  size_t bin_index = 0;

  // count frequencies in data and add to bins collection
  bins_.push_back(0); // add 0 for first value
  for (size_t data_index = 0; data_index < data.size(); data_index++) {
    if (data[data_index] >= bin_max             // transition to new bin
      ) { // TODO: remove that comment later -- IDK if data_index need it so commented it for now
      bin_min = bin_max;
      bin_max = bin_min + bin_size;
//      bin_index++;
      bins_.push_back(0);
    }
    if (data[data_index] >= bin_min && data[data_index] < bin_max) { // increment freq in bin
      bins_[bins_.size() - 1] = bins_[bins_.size() - 1] + 1;
    }
  }
}
void Histogram::Draw() {
  DrawBars();
  DrawAxis();
  DrawLabels();
}

}