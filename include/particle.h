//
// Created by amaan on 3/16/2021.
//

#include "cinder/gl/gl.h"

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

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
   * @param position x and y component of the Particle's position
   * @param velocity x and y component of the Particle's velocity
   * @param particle_color color of the particle
   * @param radius radius of the particle
   * @param mass mass of the particle
   * @param type_name   the name of the particle type. Anything you wish to name
   *                    the particle type as
   */
  Particle(glm::vec2 position, glm::vec2 velocity, ci::Color particle_color,
           float radius, float mass, std::string type_name="");

  /**
   * Particles moves one time step by using velocity
   */
  void Move();
  ci::Color GetColor() const;
  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  float GetSpeed() const;
  float GetRadius() const;
  std::string GetTypeName() const;

  /**
   * Checks if the 2 particles are touching each other.
   * Used to detect if particles are colliding.
   *
   * @param particle_one    particle one
   * @param particle_two    particle two
   * @return                true if the particles are touching each other
   */
  bool IsTouching(const Particle& other_particle)
      const;  // TODO: decide later if this method and IsApproaching() should actually be private. Do it like this for now

  /**
   * Checks if the two particles are approaching each other.
   *
   * @param particle_one    particle one
   * @param particle_two    particle two
   * @return                Returns true if the 2 particles are approaching
   *                        each other, false if they are moving away
   */
  bool IsApproaching(const Particle& other_particle) const;

  /**
    * Calculates & updates the new velocity of the particle when colliding with
    * a vertical wall
   */
  void UpdateVelocityForVerticalWallCollision();

  /**
    * Calculates & updates the new velocity of the particle when colliding with
    * a horizontal wall
   */
  void UpdateVelocityForHorizontalWallCollision();

  /**
   * Uses the equation to find the new velocity for an object in a 2D
   * image, disregarding mass of the particle. The new returned velocity is
   * for particle 1 (with velocity 1 and velocity 2), so ordering of the
   * velocity 1 and velocity 2 (same for positions) do matter.
   *
   * @param colliding_particle  The particle that the current particle is
   *                            colliding with
   */
  void UpdateVelocitiesForParticleCollision(Particle& colliding_particle);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float radius_;
  float mass_;
  std::string type_name_;

  /**
   * Uses the equation to find the new velocity for an object in a 2D
   * image, disregarding mass of the particle. The new returned velocity is
   * for particle 1.
   *
   * @param particle1   the first particle in the collision
   * @param particle2   the second particle in the collision
   */
  glm::vec2 Particle::ComputeVelocityForParticleCollision(glm::vec2& velocity1, glm::vec2& velocity2, glm::vec2& position1,
    glm::vec2& position2);

  glm::vec2 Particle::ComputeVelocityForParticleCollision(Particle& particle1, Particle& particle2);
};
}  // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_H
