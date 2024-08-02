#include "enemy/EnemySpaceship.h"

namespace ly {
EnemySpaceship::EnemySpaceship(World *owningWorld,
                               const std::string &texturePath,
                               float collisionDamage)
    : Spaceship{owningWorld, texturePath}, mCollisionDamage{collisionDamage} {
  SetTeamId(2);
}

void EnemySpaceship::OnActorOverlap(Actor *other) {
  Spaceship::OnActorOverlap(other);
  if (IsOtherHostile(other)) {
    other->ApplyDamage(mCollisionDamage);
  }
}

void EnemySpaceship::Tick(float deltaTime) {
  Spaceship::Tick(deltaTime);
  if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f)) {
    Destroy();
  }
}

}; // namespace ly