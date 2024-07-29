#include "spaceship/Spaceship.h"

namespace ly {
Spaceship::Spaceship(World *owningWorld, const std::string &texturePath)
    : Actor(owningWorld, texturePath) {}

void Spaceship::SetVelocity(const sf::Vector2f &newVelocity) {
  velocity = newVelocity;
}

sf::Vector2f Spaceship::GetVelocity() const { return velocity; }

void Spaceship::Tick(float deltaTime) {
  Actor::Tick(deltaTime);
  AddActorLocationOffset(GetVelocity() * deltaTime);
}
} // namespace ly
