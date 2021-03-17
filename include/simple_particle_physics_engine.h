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

  void UpdateParticleVelocity(Particle &particle, Particle &closest_particle,
                              glm::vec2 container_top_left,
                              glm::vec2 container_bottom_right);

//  void UpdateVelocityIfCollision

  /**
   * Calculates the new velocity of the particle if the particle collides
   * with the wall
   * @param particle
   * @param left_wall_x
   * @param right_wall_x
   * @param top_wall_y
   * @param bottom_wall_y
   * @return    true if particle collided with wall and therefore the velocity
   *            changed, and false otherwise.
   */
  bool UpdateVelocityIfWallCollision(Particle &particle,
                                     float left_wall_x, float right_wall_x,
                                     float top_wall_y, float bottom_wall_y);

  int SimpleParticlePhysicsEngine::GetNearestParticleIndex(
      int current_particle_index,
      std::vector<Particle>& particles) const;

 private:
  // TODO: should this method be private or public?
//  glm::vec2 & CalculateAfterCollisionVelocity(Particle &particle_one,
//                                             Particle &particle_two);
  bool AreParticlesColliding(Particle& particle_one, Particle& particle_two);
  bool AreParticlesMovingToEachOther(Particle& particle_one,
                                     Particle& particle_two);

  /**
   * Uses the equation to find the new velocity for an object in a 2D
   * image, disregarding mass of the particle. The new returned velocity is
   * for particle 1 (with velocity 1 and velocity 2), so ordering of the
   * velocity 1 and velocity 2 (same for positions) do matter.
   *
   * @param velocity1   velocity of particle 1
   *                    (** THE RETURNED VELOCITY IS FOR OBJECT 1)
   * @param velocity2   velocity of particle 2
   * @param position1   position of particle 1
   * @param position2   position of particle 2
   * @return            The new velocity for particle one after collision
   *                    between particle 1 and 2
   */
  glm::vec2 ComputeVelocityAfterCollision(glm::vec2 velocity1,
                                          glm::vec2 velocity2,
                                          glm::vec2 position1,
                                          glm::vec2 position2);


  bool SimpleParticlePhysicsEngine::AreEqual(float number_one, float number_two,
                                             float epsilon = 0.01f);
};
} // namespace idealgas

#endif  // IDEAL_GAS_SIMPLE_PARTICLE_PHYSICS_H
