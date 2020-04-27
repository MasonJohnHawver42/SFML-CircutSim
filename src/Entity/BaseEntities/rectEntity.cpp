#include"cbEntity.cpp"


class RectangleEntity : public CoordinateBasedEntity {
protected:
  double width;
  double height;

  sf::Color * color = new sf::Color(255, 255, 255);

public:
  RectangleEntity() : CoordinateBasedEntity() {
    width = 7.5;
    height = 10.0;
  }

  RectangleEntity(double w, double h) : CoordinateBasedEntity() {
    width = w;
    height = h;
  }

  //getters

  double getWidth() { return width; }
  double getHeight() { return height; }

  sf::Color * getColor() { return color; }

  //setters

  void setWidth(double w) { width = w; }
  void setHeight(double h) { height = h; }




  virtual void draw() {
    Viewer2D * cam = world->getViewer();
    sf::RenderWindow * window = cam->getWindow();

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(pos->getX(), pos->getY());
    rectangle.setFillColor(*color);

    window->draw(rectangle);
  }

  RectangleEntity * getCopy() {
    RectangleEntity * rect = new RectangleEntity(width, height);
    rect->setPos(pos->getCopy());
    rect->setWorld(getWorld());
    return rect;
  }

  //checkers

  virtual bool isInside(Vector<double> * point) {

    double x = point->getX() - pos->getX();
    double y = point->getY() - pos->getY();

    return (0 <= x && x <= width) && (0 <= y && y <= height);
  }

  bool isColliding(RectangleEntity * other) {
    if (pos->getX() < other->getPos()->getX() + other->getWidth() &&
         pos->getX() + width > other->getPos()->getX() &&
         pos->getY() < other->getPos()->getY() + other->getHeight() &&
         pos->getY() + height > other->getPos()->getY()) {
      // collision detected!
      return 1;
    }
    return 0;
  }
};
