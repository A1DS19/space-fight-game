#include "weapon/BulletShooter.h"
#include "framework/Core.h"

namespace ly {
BulletShooter::BulletShooter(Actor *owner, float cooldownTime)
    : Shooter(owner), mCooldownClock{}, mCooldownTime{cooldownTime} {}

bool BulletShooter::IsOnCooldown() const {
  if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime) {
    return false;
  }

  return true;
}

void BulletShooter::ShootImplementation() {
  mCooldownClock.restart();
  LOG("BulletShooter::ShootImplementation()");
}

}; // namespace ly