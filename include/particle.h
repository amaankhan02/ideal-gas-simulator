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
  Particle();
  void UpdatePosition(glm::vec2 &new_position);
  void MoveDistance(glm::vec2 &distance_vector);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  double mass_; // TODO: should these be doubles or a vector?
  double radius_;
  // TODO: add Color obj --> make a default color
};
} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_H
