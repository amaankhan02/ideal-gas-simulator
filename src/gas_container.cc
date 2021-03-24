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
  blue_particle_speeds = vector<float>();
  red_particle_speeds = vector<float>();
  green_particle_speeds = vector<float>();
  InitializeParticlesCollection();
  InitializeParticleSpeedsMap();
  UpdateParticlesSpeedMap();
}

GasContainer::GasContainer(size_t particle_count, vec2 top_left_position,
                           vec2 container_dimension, int seed, vector<Particle>& particles) {
  srand(seed);
  particle_count_ = particle_count;
  top_left_position_ = top_left_position;
  width_ = container_dimension[0];
  height_ = container_dimension[1];
  bottom_right_position =
      vec2(top_left_position_[0] + width_, top_left_position_[1] + height_);
  container_box_ = ci::Rectf(top_left_position_, bottom_right_position);
  blue_particle_speeds = vector<float>();
  red_particle_speeds = vector<float>();
  green_particle_speeds = vector<float>();
  particles_ = particles;
  InitializeParticleSpeedsMap();
  UpdateParticlesSpeedMap();
}

void GasContainer::Display() const {
  DrawContainer();
  DrawParticles();
}

void GasContainer::AdvanceOneFrame() {
  ClearParticleSpeedsMapVectors();
  for (size_t i = 0; i < particles_.size(); i++) {
    int colliding_index = GetCollidingParticleIndex(i);

    if (colliding_index == -1) { // particle didn't collide with another particle
      HandleIfWallCollision(particles_[i]);
    } else {
      particles_[i]
          .UpdateVelocitiesForParticleCollision(particles_[colliding_index]);
    }
    particle_speeds_.at(particles_[i].GetTypeName())
        .push_back(particles_[i].GetSpeed());
    particles_[i].Move();
  }
}

void GasContainer::InitializeParticlesCollection() {
  particles_ = vector<Particle>();
  for (size_t i = 0; i < particle_count_; i++) {
    // generate a random particle
    Particle particle = GenerateRandomParticle(i);
    particles_.push_back(particle);
  }
}

Particle GasContainer::GenerateRandomParticle(int particle_number) {
  // generate a random position for the particle within the container
  vec2 position;
  vec2 velocity;
  SetRandomPosition(position);
  SetRandomVelocity(velocity);

  if (particle_number % 3 == 0) {
    return Particle(position, velocity, kBlueParticleColor,
                    kBlueParticleRadius, kBlueParticleMass,
                    kBlueParticleType);
  } else if (particle_number % 3 == 1) {
    return Particle(position, velocity, kRedParticleColor, kRedParticleRadius,
                    kRedParticleMass, kRedParticleType);
  } else {
    return Particle(position, velocity, kGreenParticleColor,
                    kGreenParticleRadius, kGreenParticleMass,
                    kGreenParticleType);
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

int GasContainer::GenerateRandomInt(int lower_bound, int upper_bound) {
  return static_cast<int>(GenerateRandomFloat(
      static_cast<float>(lower_bound), static_cast<float>(upper_bound)));
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

int GasContainer::GetCollidingParticleIndex(size_t particle_index) const {
  for (size_t i = 0; i < particles_.size(); i++) {
    // checking if its colliding with a particle that's not itself
    if (particle_index == i) {
      continue;
    } else if (particles_[i].IsTouching(particles_[particle_index])
      && particles_[i].IsApproaching(particles_[particle_index])) {
      return i; // TODO: do i handle situation when it might be touching 2 particles
    }
  }

  return -1;
}

void GasContainer::HandleIfWallCollision(Particle &particle) {
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
const std::map<std::string, vector<float>>& GasContainer::GetParticleSpeeds() const {
  return particle_speeds_;
}
void GasContainer::InitializeParticleSpeedsMap() {
  particle_speeds_ = {
      { kBlueParticleType, vector<float>() },
      { kRedParticleType, vector<float>() },
      { kGreenParticleType, vector<float>() }
  };
}
void GasContainer::UpdateParticlesSpeedMap() {
  for (const auto& particle : particles_) {

  }
}
void GasContainer::ClearParticleSpeedsMapVectors() {
  particle_speeds_.at(kBlueParticleType).clear();
  particle_speeds_.at(kRedParticleType).clear();
  particle_speeds_.at(kGreenParticleType).clear();
}


}  // namespace idealgas
