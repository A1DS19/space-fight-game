#pragma once
#include "SFML/System.hpp"
#include "weapon/Shooter.h"

namespace ly {
class BulletShooter : public Shooter {
public:
  BulletShooter(Actor *owner, float cooldownTime = 1.f);
  virtual bool IsOnCooldown() const override;

private:
  virtual void ShootImplementation();
  sf::Clock mCooldownClock;
  float mCooldownTime;
};
} // namespace ly
