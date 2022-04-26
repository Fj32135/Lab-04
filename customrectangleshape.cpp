#include "customrectangleshape.hpp"

const static auto DEFAULT_COLOR = sf::Color(100, 50, 250);

CustomRectangleShape::CustomRectangleShape(const sf::Vector2f &size,
                                           const sf::Vector2f &position,
                                           const sf::Vector2u &window_size,
                                           float x_speed, float y_speed,
                                           float rotation_speed)
    : sf::RectangleShape(size), window_size_(window_size), x_speed_(x_speed),
      y_speed_(y_speed), rotation_speed_(rotation_speed) {
  setPosition(position);
  setFillColor(DEFAULT_COLOR);
}

void CustomRectangleShape::step(float time_step) {
  move(x_speed_ * time_step, y_speed_ * time_step);
  rotate(rotation_speed_ * time_step);

  sf::FloatRect bounding_box = getGlobalBounds();
  if (bounding_box.left + bounding_box.width >= window_size_.x) {
    x_speed_ = -std::abs(x_speed_);
    setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
  } else if (bounding_box.left <= 0) {
    x_speed_ = std::abs(x_speed_);
    setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
  }
  if (bounding_box.top + bounding_box.height >= window_size_.y) {
    y_speed_ = -std::abs(y_speed_);
    setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
  } else if (bounding_box.top <= 0) {
    y_speed_ = std::abs(y_speed_);
    setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
  }
}

void CustomRectangleShape::moveInDirection(float elapsed,
                                           const sf::Keyboard::Key &key) {
  if (not is_currently_selected_) {
    return;
  }

  sf::FloatRect bounding_box = getGlobalBounds();
  if (key == sf::Keyboard::Up and bounding_box.top > 0) {
    move(0, -y_speed_ * elapsed);
  } else if (key == sf::Keyboard::Down and
             bounding_box.top + bounding_box.height < window_size_.y) {
    move(0, y_speed_ * elapsed);
  } else if (key == sf::Keyboard::Left and bounding_box.left > 0) {
    move(-x_speed_ * elapsed, 0);
  } else if (key == sf::Keyboard::Right and
             bounding_box.left + bounding_box.width < window_size_.x) {
    move(x_speed_ * elapsed, 0);
  }
}

bool CustomRectangleShape::isPointedTo(
    const sf::Vector2i &mouse_position) const {
  sf::FloatRect bounding_box = getGlobalBounds();
  return bounding_box.contains(mouse_position.x, mouse_position.y);
}

void CustomRectangleShape::select() {
  setFillColor(sf::Color(255, 128, 50));
  is_currently_selected_ = true;
}

void CustomRectangleShape::deselect() {
  setFillColor(DEFAULT_COLOR);
  is_currently_selected_ = false;
}
