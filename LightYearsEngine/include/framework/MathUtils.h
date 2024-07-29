#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

namespace ly {
sf::Vector2f RotationToVector(float rotation);

float DegreesToRadians(float degrees);

float RadiansToDegrees(float radians);

template <typename T> float GetVectorLength(sf::Vector2<T> &vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

template <typename T>
sf::Vector2<T> ScaleVector(sf::Vector2<T> &vector, float scale) {
  vector.x *= scale;
  vector.y *= scale;

  return vector;
}

template <typename T> sf::Vector2<T> NormalizeVector(sf::Vector2<T> &vector) {
  float length = GetVectorLength<T>(vector);

  if (length == 0) {
    return sf::Vector2<T>{};
  }

  ScaleVector(vector, 1.0 / length);
  return vector;
}
} // namespace ly