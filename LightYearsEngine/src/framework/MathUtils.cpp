#include "framework/MathUtils.h"
#include <cmath>
#include <random>

namespace ly {

const float PI = 3.14159265359f;

sf::Vector2f RotationToVector(float rotation) {
  float radians = DegreesToRadians(rotation);
  return sf::Vector2f(std::cos(radians), std::sin(radians));
}

float DegreesToRadians(float degrees) { return degrees * (PI / 180.f); }

float RadiansToDegrees(float radians) { return radians * (180.f / PI); }

float LerpFloat(float start, float end, float alpha) {
  if (alpha > 1) {
    alpha = 1;
  }

  if (alpha < 0) {
    alpha = 0;
  }

  return start + (end - start) * alpha;
}

sf::Color LerpColor(const sf::Color &start, const sf::Color &end, float alpha) {

  float r = LerpFloat(start.r, end.r, alpha);
  float g = LerpFloat(start.g, end.g, alpha);
  float b = LerpFloat(start.b, end.b, alpha);
  float a = LerpFloat(start.a, end.a, alpha);

  return sf::Color(r, g, b, a);
}

sf::Vector2f LerpFloat(const sf::Vector2f &start, const sf::Vector2f &end,
                       float alpha) {
  float x = LerpFloat(start.x, end.x, alpha);
  float y = LerpFloat(start.y, end.y, alpha);

  return sf::Vector2f(x, y);
}

float RandomRange(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(min, max);

  return dis(gen);
}

sf::Vector2f RandomUnitVector() {
  float randomX = RandomRange(-1, 1);
  float randomY = RandomRange(-1, 1);
  sf::Vector2f randVec{randomX, randomY};
  NormalizeVector(randVec);
  return randVec;
}

sf::Vector2f LerpVector(const sf::Vector2f &a, const sf::Vector2f &b,
                        float alpha) {
  float lerpX = LerpFloat(a.x, b.x, alpha);
  float lerpY = LerpFloat(a.y, b.y, alpha);
  return sf::Vector2f(lerpX, lerpY);
}

} // namespace ly