#pragma once

namespace ly {
class Application;
class World {
public:
  World(Application *owningApp);
  virtual ~World();
  void TickInternal(float deltaTime);
  void BeginPlayInternal();

private:
  void BeginPlay();
  void Tick(float deltaTime);

  Application *mOwningApp;
  bool mBegunPlay;
};
} // namespace ly
