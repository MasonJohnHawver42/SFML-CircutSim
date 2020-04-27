#include"wire.cpp"


// does the graphics and user interface - ish

class BaseLogicGate : public Entity {
private:
  LogicGate * gate;

  RectangleEntity * body;

  InputNode ** inputNodes;
  OutputNode ** outputNodes;

  Wire ** wires;

  double buffer = .7;

  double ratio = .3; // each input / out node at least gets the width * ratio of space

  bool selected = 0;

  void init() {
    inputNodes = new InputNode*[gate->getNumOfInputs()];
    for (int i = 0; i < gate->getNumOfInputs(); i++) {
      inputNodes[i] = new InputNode(gate, i);
    }

    outputNodes = new OutputNode*[gate->getNumOfOutputs()];
    for (int i = 0; i < gate->getNumOfOutputs(); i++) {
      outputNodes[i] = new OutputNode(gate, i);
    }

    setNodes();

    wires = new Wire*[gate->getNumOfInputs()];
    for (int i = 0; i < gate->getNumOfInputs(); i++) {
      wires[i] = new Wire(inputNodes[i]);
    }
  }

public:
  BaseLogicGate(World * wrld) : Entity(wrld) {
    body = new RectangleEntity();
    body->setWorld(getWorld());

    gate = new LogicGate(wrld, 1, 1);

    setSize(20);
    init();
  }
  BaseLogicGate(LogicGate * g, World * wrld) : Entity(wrld) {
    body = new RectangleEntity();
    body->setWorld(getWorld());

    gate = g;
    gate->setWorld(getWorld());

    setSize(20);

    init();
  }
  BaseLogicGate(RectangleEntity * b, LogicGate * g, World * wrld) : Entity(wrld) {
    body = b;
    body->setWorld(getWorld());

    gate = g;
    gate->setWorld(getWorld());

    setSize(20);

    init();
  }

  //getters

  RectangleEntity * getBody() { return body; }

  bool isSeleced() { return selected; }

  LogicGate * getGate() { return gate; }

  InputNode * getInput(Vector<double> * point) {
    for(int i = 0; i< gate->getNumOfInputs(); i++) {
      if(inputNodes[i]->getBody()->isInside(point)) { return inputNodes[i]; }
    }
    return nullptr;
  }

  OutputNode * getOutput(Vector<double> * point) {
    for(int i = 0; i< gate->getNumOfOutputs(); i++) {
      if(outputNodes[i]->getBody()->isInside(point)) { return outputNodes[i]; }
    }
    return nullptr;
  }

  //setters

  void select() {
    selected = 1; body->getColor()->a = 100; body->getColor()->r = 100; body->getColor()->g = 100; body->getColor()->b = 100;
    for(int i = 0; i < gate->getNumOfInputs(); i++) {
      inputNodes[i]->select();
    }
    for(int i = 0; i < gate->getNumOfOutputs(); i++) {
      outputNodes[i]->select();
    }
  }

  void unSelect() {
    selected = 0; body->getColor()->a = 255; body->getColor()->r = 255; body->getColor()->g = 255; body->getColor()->b = 255;

    for(int i = 0; i < gate->getNumOfInputs(); i++) {
      inputNodes[i]->unSelect();
    }
    for(int i = 0; i < gate->getNumOfOutputs(); i++) {
      outputNodes[i]->unSelect();
    }
  }

  void setSize(double width) {
    body->setHeight(width * ratio * max(max(gate->getNumOfInputs(), 2), gate->getNumOfOutputs()));
    double nw = (buffer / max(max(2, gate->getNumOfInputs()), gate->getNumOfOutputs())) * body->getHeight();
    body->setWidth(width - (2*nw));
  }

  void limitSize(double w, double h) {

    double n = ratio * max(max(gate->getNumOfInputs(), 2), gate->getNumOfOutputs());

    double width = min(w, h / n);
    setSize(width);
  }

  void setPos(double x, double y) {
    double nw = (buffer / max(max(2, gate->getNumOfInputs()), gate->getNumOfOutputs())) * body->getHeight();
    body->getPos()->setX(x+nw);
    body->getPos()->setY(y);
  }

  //moders

  void move(Vector<double> * amt) {
    body->getPos()->sub(*amt);

    for(int i = 0; i < gate->getNumOfInputs(); i++) {
      inputNodes[i]->getBody()->getPos()->sub(*amt);
    }
    for(int i = 0; i < gate->getNumOfOutputs(); i++) {
      outputNodes[i]->getBody()->getPos()->sub(*amt);
    }
  }

  void resize(Vector<double> * p) {
    double w = p->getX() - body->getPos()->getX();
    double h = p->getY() - body->getPos()->getY();

    body->setWidth(max(w, 10.0));
    body->setHeight(max(10.0, h));

    setNodes();
  }

  //virtuals

  virtual BaseLogicGate * getCopy() {
    LogicGate * g = gate->getCopy();
    RectangleEntity * b = body->getCopy();

    BaseLogicGate * copy = new BaseLogicGate(b, g, getWorld());
    return copy;
  }

  virtual void draw() {
    body->getColor()->r = 170 + ((1 - gate->isUpdated()) * 50);
    body->getColor()->g = 170 + ((1 - gate->isUpdated()) * 50);
    body->getColor()->b = 170 + ((1 - gate->isUpdated()) * 50);

    body->draw();

    for(int i = 0; i < gate->getNumOfInputs(); i++) {
      wires[i]->draw();
    }

    for(int i = 0; i < gate->getNumOfInputs(); i++) {
      inputNodes[i]->draw();
    }
    for(int i = 0; i < gate->getNumOfOutputs(); i++) {
      outputNodes[i]->draw();
    }

    sf::Text text;

    // select the font
    text.setFont(*getWorld()->getAssetManager()->getFont(0)); // font is a sf::Font

    // set the string to display
    text.setString(gate->getName());
    text.setPosition (body->getPos()->getX(), body->getPos()->getY());
    double s = 50.0;
    text.setScale (1/ s, 1  /s);

    // set the character size
    text.setCharacterSize(s * body->getWidth() / 6.0); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    // inside the main loop, between window.clear() and window.display()
    getWorld()->getViewer()->getWindow()->draw(text);
  }

  virtual bool isInside(Vector<double> * point) {

    double x = point->getX() - body->getPos()->getX();
    double y = point->getY() - body->getPos()->getY();

    double size = (buffer / max(gate->getNumOfInputs(), gate->getNumOfOutputs())) * body->getHeight();

    return (0 - size <= x && x <= body->getWidth() + size) && (0 - 0 <= y && y <= body->getHeight() + 0);
  }

  void setNodes() {
    double size = (buffer / max(max(2, gate->getNumOfInputs()), gate->getNumOfOutputs())) * body->getHeight();

    Vector<double> * start = new Vector<double>(body->getPos()->getX() - size, body->getPos()->getY());
    Vector<double> * end = new Vector<double>(body->getPos()->getX() - size, body->getPos()->getY() + body->getHeight());

    setAdressNodes((AdressNode**)inputNodes, gate->getNumOfInputs(), size, start, end);

    start->add(body->getWidth() + size, 0);
    end->add(body->getWidth() + size, 0);
    setAdressNodes((AdressNode**)outputNodes, gate->getNumOfOutputs(), size, start, end);
  }
};
