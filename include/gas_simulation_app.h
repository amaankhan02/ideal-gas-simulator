#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  /**
   * Default constructor
   */
  IdealGasApp();

  /**
   * Draws contents to App
   */
  void draw() override;

  /**
   * Updates frame so that next image to be displayed is different
   * depending on collision and interaction of particles
   */
  void update() override;

  const int kWindowSize = 1600;

  /** Constant variables for Gas Container **/
  const float kGasTopLeftX = 800;
  const float kGasTopLeftY = 100;
  const float kGasWidth = 700;
  const float kGasHeight = 1200;
  const size_t kParticleCount = 30;
  const int kRandomSeed = 225;

  /** Constant variables for Histograms **/
  const float kHistogramX = 100;  // x coord for ALL histograms
  const glm::vec2 kHistogramDimension = vec2(400, 400);
  const int histogram_num_bins_ = 10;
  const std::string kYAxisLabel = "Frequency";

  const float kBlueHistogramY = 100;
  const float kRedHistogramY = 550;
  const float kGreenHistogramY = 1000;

  const ci::ColorT<float> kBlueHistogramColor = "blue";
  const ci::ColorT<float> kRedHistogramColor = "red";
  const ci::ColorT<float> kGreenHistogramColor = "green";
  const ci::ColorT<float> kHistogramAxisLabelColor = "white";

  const std::string kBlueXAxisLabel = "Blue Particle Speed";
  const std::string kRedXAxisLabel = "Red Particle Speed";
  const std::string kGreenXAxisLabel = "Green Particle Speed";

 private:
  GasContainer container_;
  Histogram blue_particle_histogram;

  Histogram red_particle_histogram;
  Histogram green_particle_histogram;
};

}  // namespace idealgas
