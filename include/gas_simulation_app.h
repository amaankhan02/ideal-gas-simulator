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

  void draw() override;
  void update() override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 1200;
  const int kMargin = 100;
  const int kParticleCount = 10;
  const int kContainerWidth = 1000;
  const int kContainerHeight = 1000; // TODO: add these changes to constructor GasContainer()

 private:
  GasContainer container_;
};

}  // namespace idealgas
