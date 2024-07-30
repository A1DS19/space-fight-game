
#include "player/PlayerSpaceship.h"
#include "framework/Core.h"
#include "framework/MathUtils.h"
#include "weapon/BulletShooter.h"

namespace ly {
PlayerSpaceship::PlayerSpaceship(World *owningWorld,
                                 const std::string &texturePath)
    : Spaceship(owningWorld, texturePath), mMoveInput{}, mSpeed{200.f},
      mBulletShooter{new BulletShooter{this, 0.2f}} {
  SetTeamId(1);
}

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

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    Shoot();
  }
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

void PlayerSpaceship::NormalizeInput() { NormalizeVector(mMoveInput); }

void PlayerSpaceship::Shoot() {
  if (mBulletShooter) {
    mBulletShooter->Shoot();
  }
}

} // namespace ly
