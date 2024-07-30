#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"
#include <string>

namespace ly {
class Spaceship : public Actor {
public:
  Spaceship(World *owningWorld, const std::string &texturePath = "");
  void Tick(float deltaTime) override;
  void SetVelocity(const sf::Vector2f &newVelocity);
  sf::Vector2f GetVelocity() const;
  virtual void Shoot();
  virtual void BeginPlay() override;

private:
  void OnHealthChanged(float amount, float health, float maxHealth);
  sf::Vector2f velocity;
  HealthComponent mHealthComponent;
};
} // namespace ly
