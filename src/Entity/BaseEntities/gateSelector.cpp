#include "Gates/baseLogicGate.cpp"

int mod(double n, double v) {
  double d = n / v;
  return v * (d - floor(d));
}



class GateSelector : public Entity {
private:
  RectangleEntity * body;

  double screenPortion = .2;
  double gapPortion = .1;
  double begin = 0;
  double num = 4.6; //num of gates shown

  std::vector<BaseLogicGate*> * gates;

public:
  GateSelector(World * wrld) : Entity(wrld) {
    body = new RectangleEntity();
    body->setWorld(getWorld());
    body->getColor()->a = 100;

    gates = new std::vector<BaseLogicGate*>();
  }

  //getters

  int getNumOfGates() { return gates->size(); }

  RectangleEntity * getBody() { return body; }

  BaseLogicGate * getGate(int index) {
    //index = mod(index, (double)gates->size());
    return gates->at(index);
  }

  BaseLogicGate * getGateCopy(int index) {
    //index = mod(index, (double)gates->size());
    return gates->at(index)->getCopy();
  }


  int getGate(Vector<double> * point) {
    double jump = (body->getWidth() / num);
    double start = body->getPos()->getX() - (begin * jump);

    double index = (point->getX() - start) / jump;

    if(index >= 0 && index < gates->size()) {
      BaseLogicGate * gate = getGate(index);
      if(gate->isInside(point)) {
        return index;
      }
    }
    return -1;
  }

  //setters

  //moders

  void addGate(BaseLogicGate * gate) {
    gate->setWorld(getWorld());
    gates->push_back(gate);
  }

  void slide(double amt, double delta) {
    begin -= amt * delta;
  }

  //virts

  void updateBody() {
    Viewer2D * cam = getWorld()->getViewer();

    body->getPos()->setX(cam->getPos()->getX());
    body->getPos()->setY(cam->getPos()->getY() + (cam->getHeight() * (1.0 - screenPortion)));

    body->setWidth(cam->getWidth());
    body->setHeight(cam->getHeight() * screenPortion);

  }

  void updateGates() {
    double jump = (body->getWidth() / num);
    double gap = gapPortion * jump;
    double start = body->getPos()->getX() - (begin * jump);

    double gateWidth = jump - gap;
    double gateHeight = body->getHeight();

    for (int i = 0; i < gates->size(); i++) {
      BaseLogicGate * gate = getGate(i);
      gate->limitSize(gateWidth, gateHeight);
      gate->setPos(start, body->getPos()->getY() + ((body->getHeight() - gate->getBody()->getHeight()) / 2.0));
      gate->setNodes();

      start += jump;
    }

    double lowerLim = 0;
    double upperLim = gates->size() - num;

    //begin = max(lowerLim, min(begin, upperLim));

  }

  virtual void update() {
    updateBody();
    updateGates();
  }

  virtual void draw() {
    body->draw();

    for(int i = floor(begin); i < ceil(begin + num); i++) {
      if(i >= 0 && i < gates->size()) {
        getGate(i)->draw();
      }
    }
  }

};
