#include <gas_container.h>
#include "particle.h"

#include <catch2/catch.hpp>

using idealgas::GasContainer;
using idealgas::Particle;
using std::vector;
using glm::vec2;

TEST_CASE("Test Constructor: Important values initialized correctly") {
  GasContainer container(10, vec2(9, 11), vec2(30, 40), 5);
  REQUIRE(container.GetParticleCount() == 10);
  REQUIRE(container.GetParticles().size() == 10);
  REQUIRE(container.GetWidth() == 30);
  REQUIRE(container.GetHeight() == 40);
  REQUIRE(container.GetTopLeftPosition()[0] == 9);
  REQUIRE(container.GetTopLeftPosition()[1] == 11);
  REQUIRE(container.GetBottomRightPosition()[0] == 39);
  REQUIRE(container.GetBottomRightPosition()[1] == 51);
}

TEST_CASE("AdvanceOneFrame Method") {
  // particle1 & 2 are colliding. Particle 3 collide w/ wall. Particle 4 is free
  Particle particle1(vec2(110, 110), vec2(3, -3), ci::Color("red"), 10, 10, "RED");
  Particle particle2(vec2(111, 111), vec2(-3, 3), ci::Color("blue"), 10, 15, "BLUE");
  Particle particle3(vec2(395, 200), vec2(2, -2), ci::Color("red"), 10, 10, "RED");
  Particle particle4(vec2(220, 220), vec2(1, -1), ci::Color("blue"), 10, 15, "BLUE");
  vector<Particle> particles = { particle1, particle2, particle3, particle4 };
  GasContainer container(3, vec2(100, 100), vec2(300, 300), 5, particles);

  SECTION("Check that particles update velocities and move to correct position") {
    REQUIRE(particle1.GetPosition() == vec2(108.2f, 113.5f));
    REQUIRE(particle2.GetPosition() == vec2(113.7f, 107.6f));
    REQUIRE(particle3.GetPosition() == vec2(393, 198));
    REQUIRE(particle4.GetPosition() == vec2(221, 219));
  }

  SECTION("Check that Speeds Map is also updated") {
    std::map<std::string, vector<float>> speeds = container.GetParticleSpeeds();
    REQUIRE(speeds.at("RED")[0] == 4.19f);
    REQUIRE(speeds.at("BLUE")[0] == 3.68f);
    REQUIRE(speeds.at("RED")[1] == 2.83f);
    REQUIRE(speeds.at("BLUE")[1] == 1);
  }
}