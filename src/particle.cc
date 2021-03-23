//
// Created by amaan on 3/16/2021.
//
#include <particle.h>

using glm::vec2;

namespace idealgas {

Particle::Particle(glm::vec2 position, glm::vec2 velocity,
                   ci::Color particle_color, float radius) {
  position_ = position;
  velocity_ = velocity;
  color_ = particle_color;
  radius_ = radius;
}
const glm::vec2& Particle::GetPosition() const {
  return position_;
}
ci::Color Particle::GetColor() const {
  return color_;
}
const glm::vec2& Particle::GetVelocity() const {
  return velocity_;
}
float Particle::GetRadius() const {
  return radius_;
}
void Particle::Move() {
  position_ += velocity_;
}
bool Particle::IsTouching(const Particle& other_particle) const {
  return false;
}
bool Particle::IsApproaching(const Particle& other_particle) const {
  return false;
}
void Particle::UpdateVelocitiesForParticleCollision(Particle& colliding_particle) {
  velocity_ = ComputeVelocityForParticleCollision(*this, colliding_particle);
  colliding_particle.velocity_ = ComputeVelocityForParticleCollision(colliding_particle, *this);
}

glm::vec2 Particle::ComputeVelocityForParticleCollision(Particle& particle1,
                                                   Particle& particle2) const {
  // calculate difference between velocities & distance between particle 1 & 2
  vec2 velocity_difference = particle1.velocity_ - particle2.velocity_;
  vec2 distance = particle1.position_ - particle2.position_;

  // compute the squared length of the distance vector
  float squared_length_of_distance = glm::length2(distance);

  // compute the fraction in the equation that multiplies the distance vector
  float multiplier =
      glm::dot(velocity_difference, distance) / squared_length_of_distance;

  // return the final answer using the equation described in method docs
  return particle1.velocity_ - (multiplier * distance);
}

}  // namespace idealgas
