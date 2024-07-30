#pragma once
#include "framework/Delegate.h"

namespace ly {
class HealthComponent {

public:
  HealthComponent(float health, float maxHealth);
  void ChangeHealth(float amount);
  float GetHealth() const { return mHealth; }
  float GetMaxHealth() const { return mMaxHealth; }
  Delegate<float, float, float> OnHealthChanged;

private:
  void TakenDamage(float amount);
  void HealthEmpty();
  void HealthRegen(float amount);
  float mHealth;
  float mMaxHealth;
};
} // namespace ly
