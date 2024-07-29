
#include "player/PlayerSpaceship.h"

namespace ly {
PlayerSpaceship::PlayerSpaceship(World *owningWorld,
                                 const std::string &texturePath)
    : Spaceship(owningWorld, texturePath), mMoveInput{}, mSpeed{200.f} {}

void PlayerSpaceship::Tick(float deltaTime) {
  Spaceship::Tick(deltaTime);
  HandleInput();
  ConsumeInput(deltaTime);
}

void PlayerSpaceship::HandleInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    mMoveInput.y = -1.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    mMoveInput.y = 1.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    mMoveInput.x = -1.f;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    mMoveInput.x = 1.f;
  }
}

void PlayerSpaceship::ConsumeInput(float deltaTime) {
  SetVelocity(mMoveInput * GetSpeed());
  mMoveInput.x = mMoveInput.y = 0.f;
}

} // namespace ly
