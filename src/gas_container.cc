#include "gas_container.h"

namespace idealgas {

using glm::vec2;
using std::vector;

GasContainer::GasContainer(size_t particle_count, vec2 top_left_position,
                           vec2 container_dimension, int seed) {
  srand(seed);
  particle_count_ = particle_count;
  top_left_position_ = top_left_position;
  width_ = container_dimension[0];
  height_ = container_dimension[1];
  bottom_right_position =
      vec2(top_left_position_[0] + width_, top_left_position_[1] + height_);
  container_box_ = ci::Rectf(top_left_position_, bottom_right_position);

  InitializeParticlesCollection();
}

void GasContainer::Display() const {
  DrawContainer();
  DrawParticles();
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    // get index of the particle colliding with the current particle
    int colliding_index = GetCollidingParticleIndex(i);

    // if particle collided with another particle update their velocities
    if (colliding_index != -1) {
      particles_[i].UpdateVelocitiesForParticleCollision(
          particles_[colliding_index]);
    } else { // check and update velocity for wall collisions (if any)
      HandleForIfWallCollision(particles_[i]);
    }

    // velocities were updated for any collisions (if any), so move
    particles_[i].Move();
  }

}
void GasContainer::InitializeParticlesCollection() {
  particles_ = vector<Particle>();
  for (size_t i = 0; i < particle_count_; i++) {
    // generate a random position for the particle within the container
    vec2 position;
    vec2 velocity;
    SetRandomPosition(position);
    SetRandomVelocity(velocity);

    Particle newParticle(position, velocity, ci::Color(kDefaultParticleColor),
                         kDefaultParticleRadius);
    particles_.push_back(newParticle);
  }
}

void GasContainer::DrawContainer() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(container_box_);
}

float GasContainer::GenerateRandomFloat(float lower_bound, float upper_bound) {
  // code derived from: https://stackoverflow.com/a/5289625/7359915
  // random = float between 0 and 1
  float random = (static_cast<float>(rand())) / static_cast<float>(RAND_MAX);
  float range = upper_bound - lower_bound;
  return (random * range) + lower_bound;
}

void GasContainer::SetRandomPosition(vec2 &position) {
  // offset each bound by a margin to make sure particle doesn't spawn too
  // close to the bounds
  float left_bound = top_left_position_[0] + kMargin;
  float right_bound = top_left_position_[0] + width_ - kMargin;
  float x_position = GenerateRandomFloat(left_bound, right_bound);

  float top_bound = top_left_position_[1] + kMargin;
  float bottom_bound = top_left_position_[1] + height_ - kMargin;
  float y_position = GenerateRandomFloat(top_bound, bottom_bound);

  position = vec2(x_position, y_position);
}

void GasContainer::DrawParticles() const {
  for (const auto &particle : particles_) {
    ci::gl::color(particle.GetColor());
    ci::gl::drawSolidCircle(particle.GetPosition(), particle.GetRadius());
  }
}
void GasContainer::SetRandomVelocity(vec2 &velocity) {
  float x_velocity =
      GenerateRandomFloat(kMinVelocityComponent, kMaxVelocityComponent);
  float y_velocity =
      GenerateRandomFloat(kMinVelocityComponent, kMaxVelocityComponent);
  velocity = vec2(x_velocity, y_velocity);
}

int GasContainer::GetCollidingParticleIndex(int particle_index) const {
  for (size_t i = 0; i < particles_.size(); i++) {
    // checking if its colliding with a particle that's not itself
    if (particle_index != i
        &&
        particles_[i].IsTouching(particles_[particle_index])
        &&
        particles_[i].IsApproaching(particles_[particle_index])) {
      return i; // TODO: do handle situation when it might be touching 2 particles
    }
  }

  return -1;
}

void GasContainer::HandleForIfWallCollision(Particle &particle) const {
  float position_x = particle.GetPosition()[0];
  float position_y = particle.GetPosition()[1];
  float radius = particle.GetRadius();

  bool is_touching_vertical_wall =
         position_x - radius <= top_left_position_[0]
      || position_x + radius >= bottom_right_position[0];
  bool is_touching_horizontal_wall =
         position_y - radius <= top_left_position_[1]
      || position_y + radius >= bottom_right_position[1];

  if (is_touching_vertical_wall) {
    particle.UpdateVelocityForVerticalWallCollision();
  } else if (is_touching_horizontal_wall) {
    particle.UpdateVelocityForHorizontalWallCollision();
  }
}

float GasContainer::GetWidth() const {
  return width_;
}
float GasContainer::GetHeight() const {
  return height_;
}
size_t GasContainer::GetParticleCount() const {
  return particle_count_;
}
const vec2 &GasContainer::GetTopLeftPosition() const {
  return top_left_position_;
}
const vec2 &GasContainer::GetBottomRightPosition() const {
  return bottom_right_position;
}
const vector<Particle> & GasContainer::GetParticles() const {
  return particles_;
}


}  // namespace idealgas
