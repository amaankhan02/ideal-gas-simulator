#include <catch2/catch.hpp>

#include <gas_container.h>
#include "simple_particle_physics_engine.h"

using idealgas::Particle;

TEST_CASE("Test Constructor: Important values initialized correctly") {
  vec2 position(2, 3);
  vec2 velocity(4, 5);
  Particle particle(position, velocity, ci::Color("red"), 10);

  REQUIRE(particle.GetColor() == "red");
  REQUIRE(particle.GetRadius() == 10);
  REQUIRE(particle.GetPosition() == position);
  REQUIRE(particle.GetVelocity() == velocity);
}

TEST_CASE("Move function") {
  vec2 position(2, 3);
  vec2 velocity(4, 5);
  Particle particle(position, velocity, ci::Color("red"), 10);

  SECTION("Move with default velocity") {
    particle.Move();
    REQUIRE(particle.GetPosition() == vec2(6, 8));
  }

  SECTION("Move after changing velocity - does it move to the updated velocity?") {
    particle.SetVelocityX(-2);
    particle.SetVelocityY(-5);
    REQUIRE(particle.GetPosition() == vec2(0, -2));
  }
}

TEST_CASE("Set Velocity Function") {
  vec2 position(2, 3);
  vec2 velocity(4, 5);
  Particle particle(position, velocity, ci::Color("red"), 10);

  SECTION("Set x component") {
    particle.SetVelocityX(7);
    REQUIRE(particle.GetPosition() == vec2(7, 5));
  }

  SECTION("Set y component") {
    particle.SetVelocityY(7);
    REQUIRE(particle.GetPosition() == vec2(4, 7));
  }
}