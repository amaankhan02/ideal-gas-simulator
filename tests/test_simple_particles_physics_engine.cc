#include <gas_container.h>

#include <catch2/catch.hpp>

#include "particle.h"
#include "simple_particle_physics_engine.h"

using idealgas::GasContainer;
using idealgas::Particle;
using idealgas::SimpleParticlePhysicsEngine;
using std::vector;

TEST_CASE("UpdateParticleVelocity for wall collisions") {
  SimpleParticlePhysicsEngine physicsEngine = SimpleParticlePhysicsEngine();
  Particle particle1(vec2(10, 9), vec2(1, -1), ci::Color("red"), 10);
  Particle particle2(vec2(20, 20), vec2(1, -1), ci::Color("red"), 10);
  Particle particle3(vec2(90, 90), vec2(1, -1), ci::Color("red"), 10);
  Particle particle4(vec2(70, 70), vec2(1, -1), ci::Color("red"), 10);
  vec2 container_top_left(0, 0);
  vec2 container_bottom_right(100, 100);

  SECTION("Collide with left wall") {
    physicsEngine.UpdateParticleVelocity(
        particle1, particle2, container_top_left, container_bottom_right);
    REQUIRE(particle1.GetVelocity()[0] == -1);
  }

  SECTION("Collide with top wall") {
    physicsEngine.UpdateParticleVelocity(
        particle1, particle2, container_top_left, container_bottom_right);
    REQUIRE(particle1.GetVelocity()[1] == 1);
  }

  SECTION("Collide with right wall") {
    physicsEngine.UpdateParticleVelocity(
        particle3, particle4, container_top_left, container_bottom_right);
    REQUIRE(particle1.GetVelocity()[0] == -1);
  }
  SECTION("Collide with bottom wall") {
    physicsEngine.UpdateParticleVelocity(
        particle3, particle4, container_top_left, container_bottom_right);
    REQUIRE(particle1.GetVelocity()[1] == 1);
  }
}

TEST_CASE("UpdateParticleVelocity for particle collisions") {
  SimpleParticlePhysicsEngine physicsEngine = SimpleParticlePhysicsEngine();

  vec2 container_top_left(0, 0);
  vec2 container_bottom_right(100, 100);

  SECTION("When particles are touching & approaching each other") {
    Particle particle1(vec2(50, 50), vec2(2, -2), ci::Color("red"), 10);
    Particle particle2(vec2(55, 56), vec2(-3, 3), ci::Color("red"), 10);

    physicsEngine.UpdateParticleVelocity(
        particle1, particle2, container_top_left, container_bottom_right);
    REQUIRE(particle1.GetVelocity() == vec2(1.9, -2.1));
    REQUIRE(particle2.GetVelocity() == vec2(5, -5.4));
  }

  SECTION("When particles are touching but already moving away") {
    Particle particle1(vec2(50, 50), vec2(2, -2), ci::Color("red"), 10);
    Particle particle2(vec2(55, 56), vec2(3, 3), ci::Color("red"), 10);

    physicsEngine.UpdateParticleVelocity(
        particle1, particle2, container_top_left, container_bottom_right);

    REQUIRE(particle1.GetVelocity() == vec2(2.1, -1.8));
    REQUIRE(particle2.GetVelocity() == vec2(4.8, -5.2));
  }
}

TEST_CASE("Test FindNearestParticleIndex") {
  SimpleParticlePhysicsEngine physicsEngine = SimpleParticlePhysicsEngine();
  Particle particle1(vec2(10, 9), vec2(1, -1), ci::Color("red"), 10);
  Particle particle2(vec2(20, 20), vec2(1, -1), ci::Color("red"), 10);
  Particle particle3(vec2(90, 90), vec2(1, -1), ci::Color("red"), 10);
  Particle particle4(vec2(70, 70), vec2(1, -1), ci::Color("red"), 10);
  vector<Particle> particles = {particle1, particle2, particle3, particle4};
  vector<Particle> single_vector_particles = {particle1};

  SECTION("Testing 4 particles") {
    int index = physicsEngine.FindNearestParticleIndex(0, particles);
    REQUIRE(index == 1);
  }

  SECTION("Testing 1 particles list") {
    int index = physicsEngine.FindNearestParticleIndex(0, single_vector_particles);
    REQUIRE(index == 0);
  }
}