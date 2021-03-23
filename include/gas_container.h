#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "histogram.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {

 public:
  const std::string kBlueParticleType = "BLUE"; // todo: can make these enums later
  const std::string kRedParticleType = "RED";
  const std::string kGreenParticleType = "GREEN";

  /**
   * Initialize GasContainer with parameters
   * @param particle_count      Number of particles
   * @param top_left_position   Coordinates (x, y) of the top left corner of the
   *                            container
   * @param container_dimension 2d vector as <width, height> of the container
   * @param seed                seed for generating random numbers
   * @param particlePhysicsEngine       a Physics engine to handle the particles
   *                            movement
   */
  GasContainer(size_t particle_count, vec2 top_left_position,
               vec2 container_dimension, int seed);
  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  const std::map<std::string, std::vector<float>>& GetParticleSpeeds() const;

  float GetWidth() const;
  float GetHeight() const;
  size_t GetParticleCount() const;
  const vec2& GetTopLeftPosition() const;
  const vec2& GetBottomRightPosition() const;
  const std::vector<Particle>& GetParticles() const;


 private:
  const float kMaxVelocityComponent = 7;

  const float kMinVelocityComponent = -kMaxVelocityComponent;
  const ci::ColorT<float> kBlueParticleColor = "blue";
  const float kBlueParticleMass = 5;
  const float kBlueParticleRadius = 20;

  const ci::ColorT<float> kRedParticleColor = "red";
  const float kRedParticleMass = 7;
  const float kRedParticleRadius = 25;

  const ci::ColorT<float> kGreenParticleColor = "green";
  const float kGreenParticleMass = 10;
  const float kGreenParticleRadius = 30;

  /** A margin from inside the container that particles should not spawn in **/
  const float kMargin = 50;

  float width_;
  float height_;
  size_t particle_count_;

  std::vector<float> blue_particle_speeds;
  std::vector<float> red_particle_speeds;
  std::vector<float> green_particle_speeds;

  /** Collection of particles inside the container **/
  std::vector<Particle> particles_;

  /** The box representing the container **/
  ci::RectT<float> container_box_;

  /** Location of the Top-Left corner of the box relative to the canvas**/
  glm::vec2 top_left_position_;

  /** Location of the Bottom-right corner of the box relative to the canvas**/
  glm::vec2 bottom_right_position;

  std::map<std::string, std::vector<float>> particle_speeds_;

  void InitializeParticlesCollection();
  void InitializeParticleSpeedsMap();
  void UpdateParticlesSpeedMap();
  void ClearParticleSpeedsMapVectors();
  void DrawContainer() const;
  void DrawParticles() const;

  int GenerateRandomInt(int lower_bound, int upper_bound);
  Particle GenerateRandomParticle(int particle_number);
  void SetRandomPosition(vec2& position);
  void SetRandomVelocity(vec2& velocity);


  /**
   * Generates a random float between lower_bound (inclusive) and
   * upper_bound (exclusive). i.e, range = [lower_bound, upper_bound)
   *
   * @param lower_bound minimum value for random number (inclusive)
   * @param upper_bound maximum value for random number (exclusive)
   * @return            a random float
   */
  float GenerateRandomFloat(float lower_bound, float upper_bound);


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
                              glm::vec2 container_bottom_right); // TODO: do i want this here? is this already in particle.h?

  /**
   * Gets the index of the particle that is currently colliding with the
   * particle at particle_index
   *
   * @param particle_index  the index (from particles_) of the particle that you
   *                        wish to check if other particles are collding with
   * @return                index of the colliding particle.
   *                        returns -1 if the particle is not colliding with
   *                        any particle
   */
  int GetCollidingParticleIndex(size_t particle_index) const;

  /**
   * Checks if the particle is colliding with a particle and calls the
   * particles update velocity for wall collision function for its respective
   * wall collision
   *
   * @param particle    particle to check if it is colliding with wall
   */
  void HandleIfWallCollision(Particle& particle);


};

}  // namespace idealgas
