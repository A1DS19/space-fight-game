#pragma once

#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ly {
class Actor;
class Application;
class World {
public:
  World(Application *owningApp);
  virtual ~World();
  void TickInternal(float deltaTime);
  void BeginPlayInternal();
  void Render(sf::RenderWindow &window);

  template <typename ActorType> weak<ActorType> SpawnActor();

  sf::Vector2u GetWindowSize() const;

private:
  void BeginPlay();
  void Tick(float deltaTime);

  Application *mOwningApp;
  bool mBegunPlay;

  List<shared<Actor>> mActors;
  List<shared<Actor>> mPendingActors;
};

template <typename ActorType> weak<ActorType> World::SpawnActor() {
  shared<ActorType> newActor{new ActorType(this)};
  mPendingActors.push_back(newActor);
  return newActor;
}
} // namespace ly
