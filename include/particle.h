//
// Created by amaan on 3/16/2021.
//

#include "cinder/gl/gl.h"

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

// TODO: do i need to put #pragma once as the first file line
// TODO: do i need those ifndef stuff
// TODO: does the include statements go before ifndef or after?

namespace idealgas {

/**
 * Represents a Particle with information about the
 * Particle's state such as Position, Velocity, etc,
 * and contains functions for modifying the Particle's state.
 */
class Particle {
 public:
  /**
   * Initializes a Particle object
   * @param position_x x component of the Particle's position
   * @param position_y y component of the Particle's position
   * @param velocity_x x component of the Particle's velocity
   * @param velocity_y y component of the Particle's velocity
   */
  Particle(glm::vec2 position, glm::vec2 velocity,
           ci::Color particle_color, float radius); // TODO: change to pass in vectors instead of pos_x etc

  void UpdatePosition(glm::vec2 &new_position);
  void MoveDistance(glm::vec2 &distance_vector);
  /**
   * Particles moves one time step by using velocity
   */
  void Move();
  ci::Color GetColor() const;
  glm::vec2 GetPosition() const;
  glm::vec2 GetVelocity() const;
  float GetRadius() const;
  void SetVelocityX(float new_velocity_x);
  void SetVelocityY(float new_velocity_y);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float mass_; // TODO: should these be doubles or a vector?
  float radius_;

};
} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_H
