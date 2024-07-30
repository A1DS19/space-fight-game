#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtils.h"
#include "framework/World.h"

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

void Actor::Tick(float DeltaTime) {}

void Actor::SetTexture(const std::string &texturePath) {
  AssetManager &assetManager = AssetManager::Get();
  mTexture = assetManager.LoadTexture(texturePath);
  if (!mTexture) {
    LOG("Failed to load texture: %s", texturePath.c_str());
    return;
  }
  mSprite.setTexture(*mTexture);

  int textureWidth = mTexture->getSize().x;
  int textureHeight = mTexture->getSize().y;

  mSprite.setTextureRect(sf::IntRect(
      sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}}));
  CenterPivot();
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

void Actor::AddActorLocationOffset(const sf::Vector2f &offsetAmt) {
  SetActorLocation(GetActorLocation() + offsetAmt);
}

void Actor::AddActorRotationOffset(float offsetAmt) {
  SetActorRotation(GetActorRotation() + offsetAmt);
}

sf::Vector2f Actor::GetActorLocation() const { return mSprite.getPosition(); }

float Actor::GetActorRotation() const { return mSprite.getRotation(); }

sf::Vector2f Actor::GetActorForwardDirection() const {
  return RotationToVector(GetActorRotation());
}

sf::Vector2f Actor::GetActorRightDirection() const {
  return RotationToVector(GetActorRotation() + 90.f);
}

void Actor::CenterPivot() {
  sf::FloatRect bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

sf::Vector2u Actor::GetWindowSize() const {
  return owningWorld->GetWindowSize();
}

bool Actor::IsActorOutOfWindowBounds() const {
  float windowWidth = GetWorld()->GetWindowSize().x;
  float windowHeight = GetWorld()->GetWindowSize().y;

  float actorWidth = GetActorGlobalBounds().width;
  float actorHeight = GetActorGlobalBounds().height;

  sf::Vector2f actorPosition = GetActorLocation();

  if (actorPosition.x < -actorWidth) {
    return true;
  }

  if (actorPosition.x > windowWidth + actorWidth) {
    return true;
  }

  if (actorPosition.y < -actorHeight) {
    return true;
  }

  if (actorPosition.y > windowHeight + actorHeight) {
    return true;
  }

  return false;
}

sf::FloatRect Actor::GetActorGlobalBounds() const {
  return mSprite.getGlobalBounds();
}

}; // namespace ly