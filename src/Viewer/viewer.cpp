#include <SFML/Graphics.hpp>
#include <math.h>
#include "../vector.cpp"

using namespace std;

class Viewer {
protected:
  sf::RenderWindow * window;

public:
  Viewer(sf::RenderWindow * w) {
    window = w;
  }

  Viewer() {
    window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Demo Game 66");
  }

  //getters

  sf::RenderWindow * getWindow() { return window; }

  //setters

  void setWindow(sf::RenderWindow * w) { window = w; }

  //other

  virtual void update() {}

};
