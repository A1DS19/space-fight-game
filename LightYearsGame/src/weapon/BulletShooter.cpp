#include "weapon/BulletShooter.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "weapon/Bullet.h"

namespace ly {
BulletShooter::BulletShooter(Actor *owner, float cooldownTime,
                             const sf::Vector2f &localPositionOffset,
                             float localRotationOffset)
    : Shooter(owner), mCooldownClock{}, mCooldownTime{cooldownTime},
      mLocalPositionOffset{localPositionOffset}, mLocalRotationOffset{
                                                     localRotationOffset} {}

bool BulletShooter::IsOnCooldown() const {
  if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime) {
    return false;
  }

  return true;
}

void BulletShooter::ShootImplementation() {
  sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
  sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

  mCooldownClock.restart();
  weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(
      GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue10.png");
  newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() +
                                     ownerForwardDir * mLocalPositionOffset.x +
                                     ownerRightDir * mLocalPositionOffset.y);
  newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() +
                                     mLocalRotationOffset);
}

}; // namespace ly