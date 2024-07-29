#pragma once
#include "spaceship/Spaceship.h"
#include "weapon/BulletShooter.h"
#include <string>

namespace ly {
class BulletShooter;
class PlayerSpaceship : public Spaceship {
public:
  PlayerSpaceship(World *owningWorld,
                  const std::string &texturePath =
                      "SpaceShooterRedux/PNG/playerShip1_blue.png");

  virtual void Tick(float deltaTime) override;
  void SetSpeed(float speed) { mSpeed = speed; }
  float GetSpeed() const { return mSpeed; }
  virtual void Shoot() override;

private:
  void HandleInput();
  sf::Vector2f mMoveInput;
  void ConsumeInput(float deltaTime);
  float mSpeed = 200.f;
  void NormalizeInput();
  void PreventOffScreenMovement();
  unique<BulletShooter> mBulletShooter;
};
} // namespace ly