#include "viewer.cpp"

class Viewer2D : public Viewer {
protected:
  Vector<double> * pos;

  double width;
  double height;

public:
  Viewer2D(sf::RenderWindow * win) : Viewer(win) {
    pos = new Vector<double>(0, 0);
    width = 100;
    height = 100;
  }

  Viewer2D() : Viewer() {
    pos = new Vector<double>(0, 0);
    width = 100;
    height = 100;
  }
  //getters

  Vector<double> * getPos() { return pos; }

  double getHeight() { return height; }
  double getWidth() { return width; }

  //setters

  void setPos(double x, double y) {
    pos->setX(x);
    pos->setY(y);
  }

  void setWidth(double w) { width = w; }
  void setHeight(double h) { height = h; }

  void setPos(Vector<double> * p) { pos = p; }

  //modders

  void zoom(double zoomFactor, double delta) {
    double factor = pow(zoomFactor, delta);

    width *= factor;
    height *= factor;
  }

  //virtual

  virtual void update() {
    sf::View view;
    view.reset(sf::FloatRect(pos->getX(), pos->getY(), width, height));
    window->setView(view);
  }



};
