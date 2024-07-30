#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"
#include "framework/Object.h"
#include <box2d/b2_body.h>

namespace ly {
class World;
class Actor : public Object {
public:
  Actor(World *owningWorld, const std::string &texturePath = "");
  virtual ~Actor();

  void BeginPlayInternal();
  virtual void BeginPlay();

  virtual void Tick(float DeltaTime);
  void SetTexture(const std::string &texturePath);

  void Render(sf::RenderWindow &window);
  void TickInternal(float deltaTime);

  void SetActorLocation(const sf::Vector2f &newLocation);
  void SetActorRotation(float newRot);

  void AddActorLocationOffset(const sf::Vector2f &offsetAmt);
  void AddActorRotationOffset(float offsetAmt);

  sf::Vector2f GetActorLocation() const;
  float GetActorRotation() const;

  sf::Vector2f GetActorForwardDirection() const;
  sf::Vector2f GetActorRightDirection() const;

  sf::Vector2u GetWindowSize() const;

  World *GetWorld() const { return owningWorld; }

  bool IsActorOutOfWindowBounds() const;

  sf::FloatRect GetActorGlobalBounds() const;

  void SetEnablePhysics(bool enablePhysics);

  virtual void OnActorOverlap(Actor *actor);
  virtual void OnActorEndOverlap(Actor *actor);

private:
  void InitializePhysics();
  void UnInitializePhysics();
  void UpdatePhysicsTransform();
  World *owningWorld;
  bool mHasBegunPlay;
  sf::Sprite mSprite;
  shared<sf::Texture> mTexture;
  void CenterPivot();
  b2Body *mPhysicsBody;
  bool mEnablePhysics;
};
}; // namespace ly