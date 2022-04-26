#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "customrectangleshape.hpp"

int main() {
  std::srand(std::time(nullptr));
  sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
  window.setVerticalSyncEnabled(true);

  const int rectangle_x_size = 120;
  const int rectangle_y_size = 60;

  std::vector<CustomRectangleShape> rectangles;
  for (int i = 0; i < 10; i++) {
    int random_x = rand() % (window.getSize().x - rectangle_x_size);
    int random_y = rand() % (window.getSize().y - rectangle_y_size);
    CustomRectangleShape rectangle(
        sf::Vector2f(rectangle_x_size, rectangle_y_size),
        sf::Vector2f(random_x, random_y), window.getSize());
    rectangles.emplace_back(rectangle);
  }
  sf::Clock clock;
  while (window.isOpen()) {
    float time_step = clock.restart().asSeconds();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return 0;
      } else if (event.type == sf::Event::KeyPressed) {
        for (auto &rectangle : rectangles) {
          rectangle.moveInDirection(time_step, event.key.code);
        }
      } else if (event.type == sf::Event::MouseButtonPressed) {
        for (auto &rectangle : rectangles) {
          if (rectangle.isPointedTo(sf::Mouse::getPosition(window))) {
            rectangle.select();
          } else {
            rectangle.deselect();
          }
        }
      }
    }
    window.clear(sf::Color::Black);

    for (auto &rectangle : rectangles) {
      window.draw(rectangle);
    }

    window.display();
  }
  return 0;
}
