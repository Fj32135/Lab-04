#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

class CustomRectangleShape : public sf::RectangleShape {
public:
  CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position,
                       const sf::Vector2u &window_size, float x_speed = 100,
                       float y_speed = 100, float rotation_speed = 50);

  void step(float time_step);
  void moveInDirection(float elapsed, const sf::Keyboard::Key &key);
  bool isPointedTo(const sf::Vector2i &mouse_position) const;
  void select();
  void deselect();

private:
  sf::Vector2u window_size_;
  float x_speed_;
  float y_speed_;
  float rotation_speed_;
  bool is_currently_selected_ = false;
};
