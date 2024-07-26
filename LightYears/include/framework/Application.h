#pragma once

#include <SFML/Graphics.hpp>

namespace ly {
class Application {
public:
  Application();
  ~Application();
  void Run();

private:
  sf::RenderWindow mWindow;
};
} // namespace ly
