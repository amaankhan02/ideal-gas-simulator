#include <gas_container.h>

#include <catch2/catch.hpp>

#include "simple_particle_physics_engine.h"

using idealgas::GasContainer;
using idealgas::SimpleParticlePhysicsEngine;

TEST_CASE("Test Constructor: Important values initialized correctly") {
  SimpleParticlePhysicsEngine physicsEngine();
  GasContainer container(10, vec2(9, 11), vec2(30, 40), 5, physicsEngine());
  REQUIRE(container.GetParticleCount() == 10);
  REQUIRE(container.GetParticles().size() == 10);
  REQUIRE(container.GetWidth() == 30);
  REQUIRE(container.GetHeight() == 40);
  REQUIRE(container.GetTopLeftPosition()[0] == 9);
  REQUIRE(container.GetTopLeftPosition()[1] == 11);
  REQUIRE(container.GetBottomRightPosition()[0] == 39);
  REQUIRE(container.GetBottomRightPosition()[1] == 51);
}