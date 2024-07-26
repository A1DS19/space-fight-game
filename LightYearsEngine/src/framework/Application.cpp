#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include <iostream>

namespace ly {
Application::Application()
    : mWindow{sf::VideoMode(1024, 1440), "Light Years"}, mTargetFrameTime{60.0},
      mTickClock{} {}

Application::~Application() { LOG("Application destroyed"); }

void Application::Tick(float deltaTime) {}

void Application::TickInternal(float deltaTime) {
  Tick(deltaTime);

  if (currentWorld) {
    currentWorld->BeginPlayInternal();
    currentWorld->TickInternal(deltaTime);
  }
};

void Application::Render() {
  sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));
  rect.setFillColor(sf::Color::Red);
  mWindow.draw(rect);
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