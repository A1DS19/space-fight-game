#include "spaceship/Spaceship.h"
#include "VFX/Explosion.h"
#include "framework/Core.h"
#include "framework/MathUtils.h"

namespace ly {
Spaceship::Spaceship(World *owningWorld, const std::string &texturePath)
    : Actor(owningWorld, texturePath), mHealthComponent{100.f, 100.f},
      mBlinkTime{0.f}, mBlinkDuration{0.2f}, mBlinkColorOffset{255, 0, 0, 255} {
}

void Spaceship::SetVelocity(const sf::Vector2f &newVelocity) {
  velocity = newVelocity;
}

sf::Vector2f Spaceship::GetVelocity() const { return velocity; }

void Spaceship::Tick(float deltaTime) {
  Actor::Tick(deltaTime);
  AddActorLocationOffset(GetVelocity() * deltaTime);
  UpdateBlink(deltaTime);
}

void Spaceship::Shoot() {}

void Spaceship::BeginPlay() {
  Actor::BeginPlay();
  SetEnablePhysics(true);
  mHealthComponent.OnHealthChanged.BindAction(GetWeakRef(),
                                              &Spaceship::OnHealthChanged);
  mHealthComponent.onTakenDamage.BindAction(GetWeakRef(),
                                            &Spaceship::OnTakenDamage);
  mHealthComponent.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::Blow);
}

void Spaceship::OnHealthChanged(float amount, float health, float maxHealth) {}

void Spaceship::ApplyDamage(float damage) {
  mHealthComponent.ChangeHealth(-damage);
}

void Spaceship::OnTakenDamage(float amount, float health, float maxHealth) {
  Blink();
}

void Spaceship::Blow(float amount, float health, float maxHealth) {
  Explosion *explosion = new Explosion();
  explosion->SpawnExplosion(GetWorld(), GetActorLocation());
  Destroy();
  delete explosion;
}

void Spaceship::Blink() {
  if (mBlinkTime == 0) {
    mBlinkTime = mBlinkDuration;
  }
}

void Spaceship::UpdateBlink(float deltaTime) {
  if (mBlinkTime > 0) {
    mBlinkTime -= deltaTime;
    mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

    GetSprite().setColor(
        LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
  }
}

} // namespace ly
