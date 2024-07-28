#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"
#include "framework/Object.h"

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

private:
  World *owningWorld;
  bool mHasBegunPlay;
  sf::Sprite mSprite;
  shared<sf::Texture> mTexture;
};
}; // namespace ly