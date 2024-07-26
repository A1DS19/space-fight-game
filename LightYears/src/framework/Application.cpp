#include "framework/Application.h"
#include <iostream>

namespace ly {
Application::Application()
    : mWindow{sf::VideoMode(1024, 1340), "Light Years"} {}

Application::~Application() {
  std::cout << "Application shutting down..." << std::endl;
}

void Application::Run() {
  while (mWindow.isOpen()) {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        mWindow.close();
      }
    }
    mWindow.clear();
    mWindow.display();
  }
}

} // namespace ly