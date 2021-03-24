//
// Created by amaan on 3/16/2021.
//
#include <particle.h>

using glm::vec2;
using std::string;

namespace idealgas {

Particle::Particle(glm::vec2 position, glm::vec2 velocity,
                   ci::Color particle_color, float radius, float mass, string type_name) {
  position_ = position;
  velocity_ = velocity;
  color_ = particle_color;
  radius_ = radius;
  mass_ = mass;
  type_name_ = type_name;
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
  // get distance between the 2 particles
  float distance = fabs(
      glm::distance(position_, other_particle.position_));

  // checks if particles are touching
  return distance <= (radius_ + other_particle.radius_);
}
bool Particle::IsApproaching(const Particle& other_particle) const {
  // logic is derived from this explanation:
  // https://math.stackexchange.com/a/1438045/824233

  // make particle 1 the observer and all else relative to particle 1
  vec2 particle_1_position = position_ - position_;
  vec2 particle_2_position = other_particle.position_ - position_;

  // do same thing for velocities: make them relative to particle 1
  vec2 particle_1_velocity = velocity_ - velocity_;
  vec2 particle_2_velocity = other_particle.velocity_ - velocity_;

  // now evaluate if particle 2 velocity is in direction of particle 1 (origin)
  float old_distance =
      fabs(glm::distance(particle_2_position, particle_1_position));
  float new_distance = fabs(glm::distance(
      particle_2_position + particle_2_velocity, particle_1_position));

  // if the new distance is shorter than the old distance,
  // then particle 2 is getting closer to (i.e. approaching) particle 1
  return new_distance < old_distance;
}
void Particle::UpdateVelocitiesForParticleCollision(Particle& colliding_particle) {
//  vec2 new_velocity_1 = ComputeVelocityForParticleCollision(velocity_, colliding_particle.velocity_, position_, colliding_particle.position_);
//  vec2 new_velocity_2 = ComputeVelocityForParticleCollision(colliding_particle.velocity_, velocity_, colliding_particle.position_, position_);

  vec2 new_velocity_1 = ComputeVelocityForParticleCollision(*this, colliding_particle);
  vec2 new_velocity_2 = ComputeVelocityForParticleCollision(colliding_particle, *this);

  velocity_ = new_velocity_1;
  colliding_particle.velocity_ = new_velocity_2;
}

glm::vec2 Particle::ComputeVelocityForParticleCollision(
    glm::vec2& velocity1, glm::vec2& velocity2, glm::vec2& position1,
    glm::vec2& position2) {

  // calculate difference between velocities & distance between particle 1 & 2
  vec2 velocity_difference = velocity1 - velocity2;
  vec2 distance = position1 - position2;

  // compute the squared length of the distance vector
  float squared_length_of_distance = glm::length2(distance);

  // compute the fraction in the equation that multiplies the distance vector
  float multiplier =
      glm::dot(velocity_difference, distance) / squared_length_of_distance;

  // return the final answer using the equation described in method docs
  return velocity1 - (multiplier * distance);
}

glm::vec2 Particle::ComputeVelocityForParticleCollision(Particle& particle1, Particle& particle2) {
  // calculate difference between velocities & distance between particle 1 & 2
  vec2 velocity_difference = particle1.velocity_ - particle2.velocity_;
  vec2 distance = particle1.position_ - particle2.position_;

  // compute the squared length of the distance vector
  float squared_length_of_distance = glm::length2(distance);

  // compute mass fraction
  float mass_fraction = 2 * particle2.mass_ / (particle1.mass_ + particle2.mass_);

  // compute the fraction in the equation that multiplies the distance vector
  float multiplier = mass_fraction * (glm::dot(velocity_difference, distance)
                       / squared_length_of_distance);

  // return the final answer using the equation described in method docs
  return particle1.velocity_ - (multiplier * distance);
}


void Particle::UpdateVelocityForVerticalWallCollision() {
  velocity_[0] *= -1; // negate x component
}
void Particle::UpdateVelocityForHorizontalWallCollision() {
  velocity_[1] *= -1; // negate y component
}
float Particle::GetSpeed() const {
  return glm::length(velocity_);
}
std::string Particle::GetTypeName() const {
  return type_name_;
}
float Particle::GetMass() {
  return mass_;
}

}  // namespace idealgas
