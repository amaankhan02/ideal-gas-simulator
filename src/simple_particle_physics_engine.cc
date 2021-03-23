//
// Created by amaan on 3/16/2021.
//

#include "simple_particle_physics_engine.h"

using glm::vec2;
using std::vector;

namespace idealgas {

// TODO: areparticlestouching and some other methods could be in particle
bool SimpleParticlePhysicsEngine::AreParticlesTouching(Particle& particle_one,
                                                       Particle& particle_two) {
  // get distance between the 2 particles
  float distance = fabs(
      glm::distance(particle_one.GetPosition(), particle_two.GetPosition()));

  // check if particles are touching
  if (distance <= (particle_one.GetRadius() + particle_two.GetRadius())) {
    return true;
  }

  return false;
}

SimpleParticlePhysicsEngine::SimpleParticlePhysicsEngine() {
}
int SimpleParticlePhysicsEngine::FindNearestParticleIndex(
    int current_particle_index, vector<Particle>& particles) const {
  vec2 current_particle_position =
      particles[current_particle_index].GetPosition();
  int closest_particle_index = 0;
  float min_distance = std::numeric_limits<float>::max();  // set to max value

  for (size_t i = 0; i < particles.size(); i++) {
    // check that the particle in the list is different from current_particle
    if (i != current_particle_index) {
      float distance =
          glm::distance(current_particle_position, particles[i].GetPosition());

      if (distance < min_distance) {  // check if we found a new min
        min_distance = distance;      // update new min values
        closest_particle_index = i;
      }
    }
  }

  return closest_particle_index;
}
void SimpleParticlePhysicsEngine::UpdateParticleVelocity(
    Particle& particle, Particle& closest_particle,
    glm::vec2 container_top_left, glm::vec2 container_bottom_right) {
  bool is_wall_collision = UpdateVelocityIfWallCollision(
      particle, container_top_left[0], container_bottom_right[0],
      container_top_left[1], container_bottom_right[1]);

  if (is_wall_collision) {
    return;  // break out if velocity was updated b/c of a wall collision
  }

  // check if particles are colliding AND moving towards each other
  if (AreParticlesTouching(particle, closest_particle) &&
      AreParticlesApproachingEachOther(particle, closest_particle)) {

    vec2 new_particle_velocity = ComputeVelocityAfterCollision(
        particle.GetVelocity(), closest_particle.GetVelocity(),
        particle.GetPosition(), closest_particle.GetPosition());
    vec2 new_other_particle_velocity = ComputeVelocityAfterCollision(
        closest_particle.GetVelocity(), particle.GetVelocity(),
        closest_particle.GetPosition(), particle.GetPosition());

    // update velocities of both particles
    particle.SetVelocityX(new_particle_velocity[0]);
    particle.SetVelocityY(new_particle_velocity[1]);
    closest_particle.SetVelocityX(new_other_particle_velocity[0]);
    closest_particle.SetVelocityY(new_other_particle_velocity[1]);
  }
}

bool SimpleParticlePhysicsEngine::UpdateVelocityIfWallCollision(
    Particle& particle, float left_wall_x, float right_wall_x, float top_wall_y,
    float bottom_wall_y) {
  float position_x = particle.GetPosition()[0];
  float position_y = particle.GetPosition()[1];
  float velocity_x = particle.GetVelocity()[0];
  float velocity_y = particle.GetVelocity()[1];
  float radius = particle.GetRadius();

  if (position_x - radius <= left_wall_x  // i.e, particle is left of left wall
      || position_x + radius >= right_wall_x) {
    particle.SetVelocityX(-velocity_x);  // negate velocity
    return true;
  } else if (position_y - radius <=
                 top_wall_y  // particle collides with horizontal wall
             || position_y + radius >= bottom_wall_y) {
    particle.SetVelocityY(-velocity_y);
    return true;
  }

  return false;
}
bool SimpleParticlePhysicsEngine::AreParticlesApproachingEachOther(
    Particle& particle_one, Particle& particle_two) {
  // logic is derived from this explanation:
  // https://math.stackexchange.com/a/1438045/824233

  // make particle 1 the observer and all else relative to particle 1
  vec2 particle_1_position =
      particle_one.GetPosition() - particle_one.GetPosition();
  vec2 particle_2_position =
      particle_two.GetPosition() - particle_one.GetPosition();

  // do same thing for velocities: make them relative to particle 1
  vec2 particle_1_velocity =
      particle_one.GetVelocity() - particle_one.GetVelocity();
  vec2 particle_2_velocity =
      particle_two.GetVelocity() - particle_one.GetVelocity();

  // now evaluate if particle 2 velocity is in direction of particle 1 (origin)
  float old_distance =
      fabs(glm::distance(particle_2_position, particle_1_position));
  float new_distance = fabs(glm::distance(
      particle_2_position + particle_2_velocity, particle_1_position));

  // if the new distance is shorter than the old distance,
  // then particle 2 is getting closer to particle 1
  if (new_distance < old_distance) {
    return true;
  } else {
    return false;
  }
}

glm::vec2 SimpleParticlePhysicsEngine::ComputeVelocityAfterCollision(
    glm::vec2 velocity1, glm::vec2 velocity2, glm::vec2 position1,
    glm::vec2 position2) {
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

}  // namespace idealgas
