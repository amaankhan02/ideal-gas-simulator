#include <gas_container.h>

#include <catch2/catch.hpp>

using glm::vec2;
using idealgas::Particle;

TEST_CASE("Test Particle Constructor: Important values initialized correctly") {
  vec2 position(2, 3);
  vec2 velocity(4, 5);
  Particle particle(position, velocity, ci::Color("red"), 10, 15, "MyName");

  REQUIRE(particle.GetColor() == "red");
  REQUIRE(particle.GetRadius() == 10);
  REQUIRE(particle.GetPosition() == position);
  REQUIRE(particle.GetVelocity() == velocity);
  REQUIRE(particle.GetMass() == 15);
  REQUIRE(particle.GetTypeName() == "MyName");
}

TEST_CASE("Move Function") {
  vec2 position(2, 3);
  vec2 velocity(4, 5);
  Particle particle(position, velocity, ci::Color("red"), 10, 15, "MyName");

  SECTION("Move with default velocity") {
    particle.Move();
    REQUIRE(particle.GetPosition() == vec2(6, 8));
  }

  SECTION("Does it move after updating velocity") {
    particle.UpdateVelocityForHorizontalWallCollision();
    particle.Move();
    REQUIRE(particle.GetPosition() == vec2(6, -2));
  }
}

TEST_CASE("Wall Collisions") {
  float mass = 15;
  std::string name = "MyName";
  Particle particle1(vec2(10, 9), vec2(1, -1), ci::Color("red"), 10, mass,
                     name);
  Particle particle2(vec2(20, 20), vec2(1, -1), ci::Color("red"), 10, mass,
                     name);

  SECTION("Collide with top wall") {
    particle1.UpdateVelocityForVerticalWallCollision();
    REQUIRE(particle1.GetVelocity()[0] == -1.0f);
  }

  SECTION("Collide with bottom wall") {
    particle1.UpdateVelocityForVerticalWallCollision();
    REQUIRE(particle1.GetVelocity()[0] == 1.0f);
  }

  SECTION("Collide with right wall") {
    particle2.UpdateVelocityForHorizontalWallCollision();
    REQUIRE(particle1.GetVelocity()[1] == -1.0f);
  }

  SECTION("Collide with left wall") {
    particle2.UpdateVelocityForHorizontalWallCollision();
    REQUIRE(particle1.GetVelocity()[1] == 1.0f);
  }
}

TEST_CASE("Particle to Particle Collisions") {
  vec2 container_top_left(0, 0);
  vec2 container_bottom_right(100, 100);

  SECTION("When particles are touching & approaching each other") {
    Particle particle1(vec2(50, 50), vec2(2, -2), ci::Color("red"), 10, 15,
                       "RedParticle");
    Particle particle2(vec2(55, 56), vec2(-3, 3), ci::Color("blue"), 10, 20,
                       "BlueParticle");

    particle1.UpdateVelocitiesForParticleCollision(particle2);
    REQUIRE(particle1.GetVelocity() == vec2(1.9, -2.1));
    REQUIRE(particle2.GetVelocity() == vec2(5, -5.4));
  }

  SECTION("When particles are touching but already moving away") {
    Particle particle1(vec2(50, 50), vec2(2, -2), ci::Color("red"), 10, 15,
                       "RedParticle");
    Particle particle2(vec2(48, 48), vec2(-3, 3), ci::Color("blue"), 10, 20,
                       "BlueParticle");

    particle1.UpdateVelocitiesForParticleCollision(particle2);
    REQUIRE(particle1.GetVelocity() == vec2(2, -2));
    REQUIRE(particle2.GetVelocity() == vec2(-3, 3));
  }

  SECTION("2 particles approaching & touching, and with 3rd far away") {
    Particle particle1(vec2(50, 50), vec2(2, -2), ci::Color("red"), 10, 15,
                       "RedParticle");
    Particle particle2(vec2(48, 48), vec2(-3, 3), ci::Color("blue"), 10, 20,
                       "BlueParticle");
    Particle particle3(vec2(100, 100), vec2(-3, 3), ci::Color("blue"), 10, 20,
                       "CoolParticle");

    particle1.UpdateVelocitiesForParticleCollision(particle2);
    REQUIRE(particle1.GetVelocity() == vec2(1.82, -2.4));
    REQUIRE(particle2.GetVelocity() == vec2(-3.4, 3.98));
    REQUIRE(particle3.GetVelocity() == vec2(-3, 3));
  }

  SECTION(
      "More than 2 particles, with 3rd touching another but not approaching "
      "either") {
    Particle particle1(vec2(50, 50), vec2(-1, 0), ci::Color("red"), 10, 15,
                       "RedParticle");
    Particle particle2(vec2(34, 50), vec2(1, 0), ci::Color("blue"), 10, 20,
                       "BlueParticle");
    Particle particle3(vec2(42, 50), vec2(0, 1), ci::Color("blue"), 10, 20,
                       "CoolParticle");

    particle1.UpdateVelocitiesForParticleCollision(particle2);
    REQUIRE(particle1.GetVelocity() == vec2(2, -2));
    REQUIRE(particle2.GetVelocity() == vec2(-3, 3));
    REQUIRE(particle3.GetVelocity() == vec2(0, 1));
  }
}