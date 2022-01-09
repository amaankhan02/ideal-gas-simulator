#include <gas_container.h>
#include <histogram.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::Histogram;
using idealgas::Particle;
using std::vector;

TEST_CASE("Test Histogram Constructor") {
  vec2 position = vec2(10, 10);
  vec2 dimension = vec2(100, 100);
  std::string x_label = "Speed";
  std::string y_label = "Frequency";
  ci::ColorT<float> axis_label_color = "white";
  ci::ColorT<float> bar_color = "blue";

  Histogram histogram(position, dimension, bar_color, axis_label_color, x_label,
                      y_label);

  REQUIRE(histogram.GetPosition() == position);
  REQUIRE(histogram.GetDimensions() == dimension);
  REQUIRE(histogram.GetXLabel() == x_label);
  REQUIRE(histogram.GetYLabel() == y_label);
  REQUIRE(histogram.GetAxisLabelColor() == axis_label_color);
  REQUIRE(histogram.GetBarColor() == bar_color);
}

TEST_CASE("UpdateData Function") {
  vec2 position = vec2(10, 10);
  vec2 dimension = vec2(99, 99);
  std::string x_label = "Speed";
  std::string y_label = "Frequency";
  ci::ColorT<float> axis_label_color = "white";
  ci::ColorT<float> bar_color = "blue";

  Histogram histogram(position, dimension, bar_color, axis_label_color, x_label,
                      y_label);

  SECTION("Empty vector of speeds") {
    vector<float> speeds = vector<float>();
    histogram.UpdateData(speeds, 5);
    REQUIRE(histogram.GetBins().empty());
  }

  SECTION("Number of bins greater than 1") {
    vector<float> speeds = {4.5, 6.7, 10, 1, 2, 5, 10, 20};
    histogram.UpdateData(speeds, 3);

    vector<int> actual_frequencies = histogram.GetBins();
    vector<int> expected_frequencies = {2, 3, 2, 0, 0, 0, 1};
    REQUIRE(histogram.GetBarWidth() == 33);
    REQUIRE(actual_frequencies.size() == 7);
    REQUIRE(actual_frequencies == expected_frequencies);
  }

  SECTION("Number of bins = 1") {
    vector<float> speeds = {4.5, 6.7, 10, 1, 2, 5, 10, 20};
    histogram.UpdateData(speeds, 1);

    vector<int> actual_frequencies = histogram.GetBins();
    vector<int> expected_frequencies = {8};
    REQUIRE(histogram.GetBarWidth() == 33);
    REQUIRE(actual_frequencies.size() == 1);
    REQUIRE(actual_frequencies == expected_frequencies);
  }
}
