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
glm::vec2 Particle::GetPosition() const {
  return position_;
}
ci::Color Particle::GetColor() const {
  return color_;
}
glm::vec2 Particle::GetVelocity() const {
  return velocity_;
}
float Particle::GetRadius() const {
  return radius_;
}
void Particle::SetVelocityX(float new_velocity_x) {
  velocity_[0] = new_velocity_x;
}
void Particle::SetVelocityY(float new_velocity_y) {
  velocity_[1] = new_velocity_y;
}
void Particle::Move() {
  position_ += velocity_;
}

}  // namespace idealgas
