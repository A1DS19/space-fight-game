
#include "player/PlayerSpaceship.h"
#include "framework/MathUtils.h"

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

  PreventOffScreenMovement();
  NormalizeInput();
}

void PlayerSpaceship::PreventOffScreenMovement() {
  sf::Vector2f position = GetActorLocation();
  sf::Vector2u windowSize = GetWindowSize();

  if (position.x < 0 && mMoveInput.x == -1) {
    mMoveInput.x = 0.f;

  } else if (position.x > windowSize.x && mMoveInput.x == 1.f) {
    mMoveInput.x = 0.f;
  }

  if (position.y < 0 && mMoveInput.y == -1) {
    mMoveInput.y = 0.f;

  } else if (position.y > windowSize.y && mMoveInput.y == 1.f) {
    mMoveInput.y = 0.f;
  }
}

void PlayerSpaceship::ConsumeInput(float deltaTime) {
  SetVelocity(mMoveInput * GetSpeed());
  mMoveInput.x = mMoveInput.y = 0.f;
}

void PlayerSpaceship::NormalizeInput() {
  NormalizeVector(mMoveInput);
  LOG("Move input is now: %f, %f", mMoveInput.x, mMoveInput.y);
}

} // namespace ly
