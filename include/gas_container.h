#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "simple_particle_physics_engine.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer { // TODO: how do i pass values into the constructor --> i get an error everytime
 public:


//
//  /**
//   * TODO: Add more parameters to this constructor, and add documentation.
//   */
//  GasContainer(int num_particles);

//  GasContainer(int particle_count, vec2 container_dimension, vec2 top_left_position);
  GasContainer();
  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

 private:
  const float kTopLeftX = 100; // TODO: do i make these 'extern' and define elsewhere?
  const float kTopLeftY = 100;
  const float kWidth = 1000;
  const float kHeight = 1000;
  const size_t kParticleCount = 15;
  const float kMinVelocityComponent = -3;
  const float kMaxVelocityComponent = 3;
  const float kDefaultParticleRadius = 30;
  const ci::ColorT<float> kDefaultParticleColor = "red";

  /** A margin from inside the container that particles should not spawn in **/
  const float kMargin = 50;

  /** Collection of particles inside the container **/
  std::vector<Particle> particles_;

  /** The box representing the container **/
  ci::RectT<float> container_box_;

  /** Location of the Top-Left corner of the box relative to the canvas**/
  glm::vec2 top_left_position_;

  /** Location of the Bottom-right corner of the box relative to the canvas**/
  glm::vec2 bottom_right_position;

  SimpleParticlePhysicsEngine physicsEngine_;

  void InitializeParticlesCollection();
  void DrawContainer() const;
  void DrawParticles() const;

  /**
   * Generates a random integer between lower_bound (inclusive) and
   * upper_bound (exclusive). i.e, range = [lower_bound, upper_bound)
   *
   * @param lower_bound minimum value for random number (inclusive)
   * @param upper_bound maximum value for random number (exclusive)
   * @return            a random integer
   */
  int GenerateRandomInt(int lower_bound, int upper_bound);

  /**
   * Generates a random float between lower_bound (inclusive) and
   * upper_bound (exclusive). i.e, range = [lower_bound, upper_bound)
   *
   * @param lower_bound minimum value for random number (inclusive)
   * @param upper_bound maximum value for random number (exclusive)
   * @return            a random float
   */
  float GenerateRandomFloat(float lower_bound, float upper_bound);
  void SetRandomPosition(vec2& position);
  void SetRandomVelocity(vec2& velocity);
};

}  // namespace idealgas
