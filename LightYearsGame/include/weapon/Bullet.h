#pragma once
#include "framework/Actor.h"

namespace ly {
class Bullet : public Actor {
public:
  Bullet(World *world, Actor *owner, const std::string &texturePath,
         float speed = 600.f, float damage = 10.f);

  void SetSpeed(float speed);
  void SetDamage(float damage);

  virtual void Tick(float deltaTime) override;
  virtual void BeginPlay() override;

  float GetDamage() const { return mDamage; }

private:
  virtual void OnActorOverlap(Actor *otherActor) override;
  void Move(float deltaTime);
  Actor *mOwner;
  float mSpeed;
  float mDamage;
};

} // namespace ly
