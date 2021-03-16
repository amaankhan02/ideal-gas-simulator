//
// Created by amaan on 3/16/2021.
//

#include "cinder/gl/gl.h"
#include "particle.h"

#ifndef IDEAL_GAS_SIMPLE_PARTICLE_PHYSICS_H
#define IDEAL_GAS_SIMPLE_PARTICLE_PHYSICS_H

namespace idealgas {

/**
 * Provides Simple Physics logic and functionality for a Particle.
 * Specifically, this engine does not take into account the mass of a particle
 * in moving a particle. Assumes that all particles are the same mass
 */
class SimpleParticlePhysicsEngine { // TODO: have it implement the interface
 public:
  SimpleParticlePhysicsEngine();
  bool AreParticlesColliding(Particle &particle_one, Particle &particle_two);
  void MoveParticle(Particle &particle, glm::vec2 &distance);

 private:
  // TODO: should this method be private or public?
  &glm::vec2 CalculateAfterCollisionVelocity(Particle &particle_one,
                                             Particle &particle_two)
};
} // namespace idealgas

#endif  // IDEAL_GAS_SIMPLE_PARTICLE_PHYSICS_H
