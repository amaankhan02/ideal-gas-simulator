#include "gas_simulation_app.h"

using std::string;
using std::vector;
using std::map;

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(kParticleCount, vec2(kGasTopLeftX, kGasTopLeftY),
vec2(kGasWidth, kGasHeight), kRandomSeed),
      blue_particle_histogram(vec2(kHistogramX, kBlueHistogramY), kHistogramDimension, kBlueHistogramColor, kHistogramAxisLabelColor, kBlueXAxisLabel, kYAxisLabel),
      red_particle_histogram(vec2(kHistogramX, kRedHistogramY), kHistogramDimension, kRedHistogramColor, kHistogramAxisLabelColor, kRedXAxisLabel, kYAxisLabel),
      green_particle_histogram(vec2(kHistogramX, kGreenHistogramY), kHistogramDimension, kGreenHistogramColor, kHistogramAxisLabelColor, kGreenXAxisLabel, kYAxisLabel){
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
  blue_particle_histogram.Draw();
  red_particle_histogram.Draw();
  green_particle_histogram.Draw();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
  map<string, vector<float>> speeds = container_.GetParticleSpeeds();
  blue_particle_histogram.UpdateData(speeds.at(container_.kBlueParticleType),
                                     histogram_num_bins_);
  red_particle_histogram.UpdateData(speeds.at(container_.kRedParticleType),
                                    histogram_num_bins_);
  green_particle_histogram.UpdateData(speeds.at(container_.kGreenParticleType),
                                      histogram_num_bins_);
}

}  // namespace idealgas
