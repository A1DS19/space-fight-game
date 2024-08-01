#pragma once

#include "enemy/EnemySpaceship.h"
#include "framework/Core.h"

namespace ly {
class BulletShooter;
class Vanguard : public EnemySpaceship {
public:
  Vanguard(World *owningWorld, const sf::Vector2f &velocity = {0.f, 150.f},
           const std::string &texturePath =
               "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png");

  virtual void Tick(float deltaTime) override;

private:
  virtual void Shoot() override;
  unique<BulletShooter> mShooter;
};
}; // namespace ly
