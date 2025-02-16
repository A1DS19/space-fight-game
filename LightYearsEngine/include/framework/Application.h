#pragma once

#include <SFML/Graphics.hpp>
#include <framework/Core.h>

namespace ly {
class World;
class Application {
public:
  Application(unsigned int windowWidth, unsigned int windowHeight,
              const std::string &windowTitle, sf::Uint32 style);
  ~Application();
  void Run();
  template <typename WorldType> weak<WorldType> LoadWorld();
  sf::Vector2u GetWindowSize() const;

private:
  void TickInternal(float deltaTime);
  void RenderInternal();

  virtual void Tick(float deltaTime);
  virtual void Render();

  sf::RenderWindow mWindow;
  float mTargetFrameTime;
  sf::Clock mTickClock;

  shared<World> pendingWorld;
  shared<World> currentWorld;

  sf::Clock mCleanCycleClock;
  float mCleanCycleInterval;
};

template <typename WorldType> weak<WorldType> Application::LoadWorld() {
  shared<WorldType> newWorld{new WorldType{this}};
  pendingWorld = newWorld;
  return newWorld;
}
} // namespace ly
