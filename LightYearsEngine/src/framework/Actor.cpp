#include "framework/Actor.h"
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
  if (!mTexture.loadFromFile(texturePath)) {
    LOG("Failed to load texture from %s", texturePath.c_str());
  }
  mSprite.setTexture(mTexture);

  int textureWidth = mTexture.getSize().x;
  int textureHeight = mTexture.getSize().y;

  mSprite.setTextureRect(sf::IntRect(
      sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}}));
}

void Actor::Render(sf::RenderWindow &window) {
  if (isPendingDestroy()) {
    return;
  }

  window.draw(mSprite);
}

}; // namespace ly