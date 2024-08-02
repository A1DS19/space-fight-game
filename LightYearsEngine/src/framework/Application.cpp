#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include <iostream>

namespace ly {
Application::Application(unsigned int windowWidth, unsigned int windowHeight,
                         const std::string &windowTitle, sf::Uint32 style)
    : mWindow{sf::VideoMode(windowWidth, windowHeight), windowTitle, style},
      mTargetFrameTime{60.0}, mTickClock{}, mCleanCycleClock{},
      mCleanCycleInterval{2.f} {}

Application::~Application() {}

void Application::Tick(float deltaTime) {}

void Application::TickInternal(float deltaTime) {
  Tick(deltaTime);

  if (currentWorld) {
    currentWorld->TickInternal(deltaTime);
  }

  TimerManager::Get().UpdateTimer(deltaTime);

  PhysicsSystem::Get().Step(deltaTime);

  if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval) {
    mCleanCycleClock.restart();
    AssetManager::Get().CleanCycle();
    if (currentWorld) {
      currentWorld->CleanCycle();
    }
  }

  if (pendingWorld && pendingWorld != currentWorld) {
    currentWorld = pendingWorld;
    currentWorld->BeginPlayInternal();
  }
};

sf::Vector2u Application::GetWindowSize() const { return mWindow.getSize(); }

void Application::Render() {
  if (currentWorld) {
    currentWorld->Render(mWindow);
  }
}

void Application::RenderInternal() {
  mWindow.clear();
  Render();
  mWindow.display();
}

void Application::Run() {
  mTickClock.restart();
  float accumulatedTime = 0.f;
  float targetDeltaTime = 1.f / mTargetFrameTime;

  while (mWindow.isOpen()) {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        mWindow.close();
      }
    }

    accumulatedTime += mTickClock.restart().asSeconds();
    while (accumulatedTime > targetDeltaTime) {
      accumulatedTime -= targetDeltaTime;
      TickInternal(targetDeltaTime);
      RenderInternal();
    }
  }
}

} // namespace ly