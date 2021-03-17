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
class SimpleParticlePhysicsEngine {
 public:
  /**
   * Default constructor
   */
  SimpleParticlePhysicsEngine();

  /**
   * Checks for any collisions (wall or other particle collisions) and
   * updates the velocity of particle & closest_particle respectfully
   * depending on the condition.
   *
   * @param particle                The current particle to be viewed and
   *                                checked for any collision
   * @param closest_particle        The nearest particle to 'particle' object
   *                                and is updated as well if there is a
   *                                collision between particle and
   *                                closest_particle
   * @param container_top_left      top left coordinates of the container
   *                                that the particle is in. Represented as
   *                                <x, y> coordinates
   * @param container_bottom_right  bottom right coordinates of the container
   *                                that the particle is in. Represented as
   *                                <x, y> coordinates
   */
  void UpdateParticleVelocity(Particle& particle, Particle& closest_particle,
                              glm::vec2 container_top_left,
                              glm::vec2 container_bottom_right);

  /**
   * Finds the nearest particle to the particle which is under question
   *
   * @param current_particle_index  The index of the particle from 'particles'
   *                                collection that you wish to find the
   *                                nearest particle to
   * @param particles               Vector of all particles that you wish to
   *                                search through to find the nearest particle
   *                                to the particle under question, which is
   *                                represented by the current_particle_index
   * @return                        index of particles collection of the
   *                                nearest particle to the particle under
   *                                question.
   */
  int SimpleParticlePhysicsEngine::FindNearestParticleIndex(
      int current_particle_index, std::vector<Particle>& particles) const;

 private:
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
  bool UpdateVelocityIfWallCollision(Particle& particle, float left_wall_x,
                                     float right_wall_x, float top_wall_y,
                                     float bottom_wall_y);

  /**
   * Checks if the 2 particles are touching each other.
   * Used to detect if particles are colliding.
   *
   * @param particle_one    particle one
   * @param particle_two    particle two
   * @return                true if the particles are touching each other
   */
  bool AreParticlesTouching(Particle& particle_one, Particle& particle_two);

  /**
   * Checks if the two particles are approaching each other.
   *
   * @param particle_one    particle one
   * @param particle_two    particle two
   * @return                Returns true if the 2 particles are approaching
   *                        each other, false if they are moving away
   */
  bool AreParticlesApproachingEachOther(Particle& particle_one,
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
};
}  // namespace idealgas

#endif  // IDEAL_GAS_SIMPLE_PARTICLE_PHYSICS_H
