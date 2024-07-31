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
  virtual void ApplyDamage(float damage) override;

private:
  virtual void OnHealthChanged(float amount, float health, float maxHealth);
  virtual void OnTakenDamage(float amount, float health, float maxHealth);
  virtual void Blow(float amount, float health, float maxHealth);
  void Blink();
  void UpdateBlink(float deltaTime);
  sf::Vector2f velocity;
  HealthComponent mHealthComponent;
  float mBlinkTime;
  float mBlinkDuration;
  sf::Color mBlinkColorOffset;
};
}; // namespace ly
