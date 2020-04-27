#include "gateSelector.cpp"

class MouseCursor : public CoordinateBasedEntity {
protected:
  double size;

  sf::Color * color = new sf::Color(0, 0, 0, 255);

public:
  MouseCursor(World * w) : CoordinateBasedEntity(w) {
    size = 2;
  }

  //getters

  Vector<double> * getScreenPos() {

    Viewer2D * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    Vector<double> * screenPos = new Vector<double>(pos->getX(), pos->getY());
    screenPos->sub(*cam->getPos());

    Vector<double> * transform = new Vector<double>(window->getSize().x / cam->getWidth(), window->getSize().y / cam->getHeight());
    screenPos->mult(*transform);

    delete transform;

    return screenPos;
  }

  //setters

  void setPosFromScreenPos(Vector<double> * sp) {

    Viewer2D * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    Vector<double> * transform = new Vector<double>(window->getSize().x / cam->getWidth(), window->getSize().y / cam->getHeight());

    sp->div(*transform);
    sp->add(*cam->getPos());

    pos->setX(sp->getX());
    pos->setY(sp->getY());

    delete transform;
  }

  //virtuals

  void limitPos() {
    Viewer2D * cam = world->getViewer();

    double minX = cam->getPos()->getX();
    double minY = cam->getPos()->getY();

    double maxX = minX + cam->getWidth();
    double maxY = minY + cam->getHeight();

    pos->setX(min(maxX, max(minX, pos->getX())));
    pos->setY(min(maxY, max(minY, pos->getY())));
  }

  void updatePos() {
    sf::Vector2i p = sf::Mouse::getPosition(*world->getViewer()->getWindow());
    Vector<double> * sp = new Vector<double>(p.x, p.y);

    setPosFromScreenPos(sp);
    delete sp;
  }

  virtual void update() {
    updatePos();
    limitPos();
  }

  virtual void draw() {

    Viewer2D * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    window->setMouseCursorVisible(0);

    sf::CircleShape shape(size);
    shape.setPosition(pos->getX() - size, pos->getY() - size);
    shape.setFillColor(sf::Color(255, 255, 255, 100));

    shape.setOutlineThickness(size * .2);
    shape.setOutlineColor(*color);

    window->draw(shape);
  }
};
