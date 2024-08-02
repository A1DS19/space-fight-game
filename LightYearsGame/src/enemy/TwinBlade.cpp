#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly {
TwinBlade::TwinBlade(World *owningWorld, const sf::Vector2f &velocity,
                     const std::string &texturePath)
    : EnemySpaceship(owningWorld, texturePath), mShooterLeft{new BulletShooter{
                                                    this, 1.f, {50.f, -20.f}}},
      mShooterRight{new BulletShooter{this, 1.f, {50.f, 20.f}, 10.f}} {
  SetVelocity(velocity);
}

void TwinBlade::Tick(float deltaTime) {
  EnemySpaceship::Tick(deltaTime);
  Shoot();
}

void TwinBlade::Shoot() {
  mShooterLeft->Shoot();
  mShooterRight->Shoot();
}

} // namespace ly
