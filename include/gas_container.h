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
class GasContainer {
 public:
  /**
   * Initialize GasContainer with parameters
   * @param particle_count      Number of particles
   * @param top_left_position   Coordinates (x, y) of the top left corner of the
   *                            container
   * @param container_dimension 2d vector as <width, height> of the container
   * @param seed                seed for generating random numbers
   * @param particlePhysicsEngine       a Physics engine to handle the particles
   *                            movement
   */
  GasContainer(size_t particle_count, vec2 top_left_position,
               vec2 container_dimension, int seed,
               SimpleParticlePhysicsEngine particlePhysicsEngine);
  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  float GetWidth() const;
  float GetHeight() const;
  size_t GetParticleCount() const;
  const vec2& GetTopLeftPosition() const;
  const vec2& GetBottomRightPosition() const;
  const std::vector<Particle>& GetParticles() const;

 private:
  const float kMaxVelocityComponent = 10;
  const float kMinVelocityComponent = -kMaxVelocityComponent;
  const float kDefaultParticleRadius = 30;
  const ci::ColorT<float> kDefaultParticleColor = "red";

  /** A margin from inside the container that particles should not spawn in **/
  const float kMargin = 50;

  float width_;
  float height_;
  size_t particle_count_;

  /** Collection of particles inside the container **/
  std::vector<Particle> particles_;

  /** The box representing the container **/
  ci::RectT<float> container_box_;

  /** Location of the Top-Left corner of the box relative to the canvas**/
  glm::vec2 top_left_position_;

  /** Location of the Bottom-right corner of the box relative to the canvas**/
  glm::vec2 bottom_right_position;

  /** A Particle Physics Engine object to handle the movements of particles **/
  SimpleParticlePhysicsEngine particlePhysicsEngine;

  void InitializeParticlesCollection();
  void DrawContainer() const;
  void DrawParticles() const;

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
