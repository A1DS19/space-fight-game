#pragma once
#include "spaceship/Spaceship.h"
#include <string>

namespace ly {
class PlayerSpaceship : public Spaceship {
public:
  PlayerSpaceship(World *owningWorld,
                  const std::string &texturePath =
                      "SpaceShooterRedux/PNG/playerShip1_blue.png");

  virtual void Tick(float deltaTime) override;
  void SetSpeed(float speed) { mSpeed = speed; }
  float GetSpeed() const { return mSpeed; }

private:
  void HandleInput();
  sf::Vector2f mMoveInput;
  void ConsumeInput(float deltaTime);
  float mSpeed = 200.f;
  void NormalizeInput();
  void PreventOffScreenMovement();
};
} // namespace ly