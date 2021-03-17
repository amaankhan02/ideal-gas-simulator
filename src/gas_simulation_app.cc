#include "gas_simulation_app.h"

namespace idealgas {

IdealGasApp::IdealGasApp()
    : container_(kParticleCount, vec2(kTopLeftX, kTopLeftY),
                 vec2(kWidth, kHeight), kRandomSeed, kPhysicsEngine) {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void IdealGasApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  container_.Display();
}

void IdealGasApp::update() {
  container_.AdvanceOneFrame();
}

}  // namespace idealgas
