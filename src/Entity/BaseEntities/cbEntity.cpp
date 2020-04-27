#include"entity.cpp"

class CoordinateBasedEntity : public Entity {
protected:
  Vector<double> * pos;

public:
  CoordinateBasedEntity(World * wrld) : Entity(wrld) {
    pos = new Vector<double>(10, 10);
  }

  CoordinateBasedEntity() : Entity() {
    pos = new Vector<double>(10, 10);
  }

  //getters

  Vector<double> * getPos() { return pos; }

  //setters

  void setPos(Vector<double> * p) { pos = p; }
  void setPos(double x, double y) {
    pos->setX(x);
    pos->setY(y);
  }

};
