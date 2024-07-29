#include "weapon/Shooter.h"

namespace ly {
void Shooter::Shoot() {
  if (CanShoot() && !IsOnCooldown()) {
    ShootImplementation();
  }
}

Shooter::Shooter(Actor *owner) : mOwner(owner) {}
} // namespace ly