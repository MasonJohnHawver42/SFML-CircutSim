#include "inputNode.cpp"

class Wire : public Entity {
protected:
  InputNode * in;

public:
  Wire(InputNode * i) : Entity() {
    in = i;

    setWorld(in->getWorld());
  }

  Vector<double> * getStart() {
    Vector<double> * pos = new Vector<double>(0, 0);
    pos->add(in->getBody()->getWidth(), in->getBody()->getHeight());
    pos->div(2.0);
    pos->add(*in->getBody()->getPos());

    return pos;
  }

  Vector<double> * getEnd() {
    OutputNode * out = in->getConnection();

    if(out) {
      Vector<double> * pos = new Vector<double>(0, 0);
      pos->add(out->getBody()->getWidth(), out->getBody()->getHeight());
      pos->div(2.0);
      pos->add(*out->getBody()->getPos());

      return pos;
    }

    return getStart();

  }

  virtual void draw() {

    if(in->getConnection()) {

      Vector<double> * start = getStart();
      Vector<double> * end = getEnd();

      double width = .5;

      Vector<double> * perp = new Vector<double>(0, 0); perp->add(*end); perp->sub(*start); perp->perp(); perp->setMag(width);

      Vector<double> * corner1 = new Vector<double>(0, 0); corner1->add(*start); corner1->add(*perp);
      Vector<double> * corner2 = new Vector<double>(0, 0); corner2->add(*start); corner2->sub(*perp);

      Vector<double> * corner3 = new Vector<double>(0, 0); corner3->add(*end); corner3->add(*perp);
      Vector<double> * corner4 = new Vector<double>(0, 0); corner4->add(*end); corner4->sub(*perp);

      sf::ConvexShape polygon;
      polygon.setPointCount(4);
      polygon.setPoint(0, sf::Vector2f(corner1->getX(), corner1->getY()));
      polygon.setPoint(1, sf::Vector2f(corner2->getX(), corner2->getY()));
      polygon.setPoint(3, sf::Vector2f(corner3->getX(), corner3->getY()));
      polygon.setPoint(2, sf::Vector2f(corner4->getX(), corner4->getY()));
      polygon.setFillColor(sf::Color(200, 40, 80));

      world->getViewer()->getWindow()->draw(polygon);

      delete start, end, perp, corner1, corner4, corner2, corner3;
    }
  }

};
