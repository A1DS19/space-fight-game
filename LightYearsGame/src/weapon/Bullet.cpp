#include "weapon/Bullet.h"
#include "framework/Core.h"

namespace ly {

Bullet::Bullet(World *world, Actor *owner, const std::string &texturePath,
               float speed, float damage)
    : Actor(world, texturePath), mOwner{owner}, mSpeed{speed}, mDamage{damage} {
  SetTeamId(owner->GetTeamId());
}

void Bullet::SetSpeed(float speed) { mSpeed = speed; }

void Bullet::SetDamage(float damage) { mDamage = damage; }

void Bullet::Tick(float deltaTime) {
  Actor::Tick(deltaTime);
  Move(deltaTime);

  if (IsActorOutOfWindowBounds()) {
    Destroy();
  }
}

void Bullet::Move(float deltaTime) {
  AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
}

void Bullet::BeginPlay() {
  Actor::BeginPlay();
  SetEnablePhysics(true);
}

void Bullet::OnActorOverlap(Actor *otherActor) {
  if (IsOtherHostile(otherActor)) {
    otherActor->ApplyDamage(GetDamage());
    Destroy();
  }
}

} // namespace ly
