#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly {
Vanguard::Vanguard(World *owningWorld, const sf::Vector2f &velocity,
                   const std::string &texturePath)
    : EnemySpaceship{owningWorld, texturePath}, mShooter{
                                                    new BulletShooter{this}} {
  SetVelocity(velocity);
  SetActorRotation(180.f);
}

void Vanguard::Shoot() { mShooter->Shoot(); }

void Vanguard::Tick(float deltaTime) {
  EnemySpaceship::Tick(deltaTime);
  Shoot();
}

}; // namespace ly