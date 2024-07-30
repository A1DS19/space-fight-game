#include "spaceship/Spaceship.h"
#include "framework/Core.h"

namespace ly {
Spaceship::Spaceship(World *owningWorld, const std::string &texturePath)
    : Actor(owningWorld, texturePath), mHealthComponent{100.f, 100.f} {}

void Spaceship::SetVelocity(const sf::Vector2f &newVelocity) {
  velocity = newVelocity;
}

sf::Vector2f Spaceship::GetVelocity() const { return velocity; }

void Spaceship::Tick(float deltaTime) {
  Actor::Tick(deltaTime);
  AddActorLocationOffset(GetVelocity() * deltaTime);
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

void Spaceship::OnTakenDamage(float amount, float health, float maxHealth) {}

void Spaceship::Blow(float amount, float health, float maxHealth) { Destroy(); }

} // namespace ly
