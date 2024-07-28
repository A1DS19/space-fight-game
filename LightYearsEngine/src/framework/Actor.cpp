#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"

namespace ly {
Actor::Actor(World *owningWorld, const std::string &texturePath)
    : owningWorld(owningWorld), mHasBegunPlay{false}, mSprite{}, mTexture{} {
  SetTexture(texturePath);
}

Actor::~Actor() { LOG("Actor::~Actor destroyed"); }

void Actor::BeginPlayInternal() {
  if (!mHasBegunPlay) {
    mHasBegunPlay = true;
    BeginPlay();
  }
}

void Actor::TickInternal(float deltaTime) {
  if (!isPendingDestroy()) {
    Tick(deltaTime);
  }
}

void Actor::BeginPlay() { LOG("Actor::BeginPlay"); }

void Actor::Tick(float DeltaTime) { LOG("Actor::Tick"); }

void Actor::SetTexture(const std::string &texturePath) {
  AssetManager &assetManager = AssetManager::Get();
  mTexture = assetManager.LoadTexture(texturePath);
  if (!mTexture) {
    return;
  }
  mSprite.setTexture(*mTexture);

  int textureWidth = mTexture->getSize().x;
  int textureHeight = mTexture->getSize().y;

  mSprite.setTextureRect(sf::IntRect(
      sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}}));
}

void Actor::Render(sf::RenderWindow &window) {
  if (isPendingDestroy()) {
    return;
  }

  window.draw(mSprite);
}

void Actor::SetActorLocation(const sf::Vector2f &newLocation) {
  mSprite.setPosition(newLocation);
}

void Actor::SetActorRotation(float newRot) { mSprite.setRotation(newRot); }

}; // namespace ly