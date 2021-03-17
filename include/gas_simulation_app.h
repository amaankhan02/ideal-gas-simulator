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

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 1200;
  const float kTopLeftX = 100;
  const float kTopLeftY = 100;
  const float kWidth = 1000;
  const float kHeight = 1000;
  const size_t kParticleCount = 15;
  const int kRandomSeed = 100;

 private:
  GasContainer container_;
};

}  // namespace idealgas
