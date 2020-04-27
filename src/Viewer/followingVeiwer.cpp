#include "2DViewer.cpp"

class FollowingVeiwer : public Viewer2D {
private:
  Vector<double> * target;

  double horizontalBound;
  double verticalBound;

public:
  FollowingVeiwer(Vector<double> * t, sf::RenderWindow * win) : Viewer2D(win) {
    target = t;

    horizontalBound = 10;
    verticalBound = 10;
  }
  FollowingVeiwer(sf::RenderWindow * win) : Viewer2D(win) {
    target = new Vector<double>(0, 0);

    horizontalBound = 150;
    verticalBound = 100;
  }
  FollowingVeiwer(Vector<double> * t) : Viewer2D() {
    target = t;

    horizontalBound = 100;
    verticalBound = 100;
  }
  FollowingVeiwer() : Viewer2D() {
    target = new Vector<double>(0, 0);

    horizontalBound = 10;
    verticalBound = 10;
  }

  //getters

  Vector<double> * getTargetPos() { return target; }

  double getHorizontalBound() { return horizontalBound; }
  double getVertical() { return verticalBound; }

  //setters

  void setTargetPos(Vector<double> * t) { target = t; }

  void setHorizontalBound(double h) {horizontalBound = h;}
  void setVerticalBound(double v) { verticalBound = v; }

  //other

  virtual void updatePos() {

    Vector<double> * boundPos = new Vector<double>(pos->getX(), pos->getY());
    boundPos->add(width / 2.0, height / 2.0);
    boundPos->sub(horizontalBound / 2.0, verticalBound/ 2.0);

    double horizontalShift = 0;
    horizontalShift += ( target->getX() >= boundPos->getX() ? 0 : target->getX() - boundPos->getX());
    horizontalShift += ( target->getX() <= boundPos->getX() + horizontalBound ? 0 : target->getX() - (boundPos->getX() + horizontalBound));

    double verticalShift = 0;
    verticalShift += ( target->getY() >= boundPos->getY() ? 0 : target->getY() - boundPos->getY());
    verticalShift += ( target->getY() <= boundPos->getY() + verticalBound ? 0 : target->getY() - (boundPos->getY() + verticalBound));

  //  target->sub(horizontalShift, verticalShift);
  //  pos->add(horizontalShift, verticalShift);

    delete boundPos;

  }

  virtual void update() {
    Viewer2D::update();
    updatePos();
  }
};
