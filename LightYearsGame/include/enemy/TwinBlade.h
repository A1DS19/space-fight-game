#pragma once

#include "enemy/EnemySpaceship.h"

namespace ly {
class BulletShooter;
class TwinBlade : public EnemySpaceship {
public:
  TwinBlade(World *owningWorld, const sf::Vector2f &velocity = {0.f, 120.f},
            const std::string &texturePath =
                "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png");
  virtual void Tick(float deltaTime) override;
  virtual void Shoot() override;

private:
  unique<BulletShooter> mShooterLeft;
  unique<BulletShooter> mShooterRight;
};
} // namespace ly
