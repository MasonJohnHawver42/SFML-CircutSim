#include"negator.cpp"

class AdressNode : public Entity {
protected:
  LogicGate * parent;
  int index;

  RectangleEntity * body;

public:
  AdressNode(LogicGate * g, int i) : Entity() {
    parent = g;
    index = i;

    setWorld(parent->getWorld());

    body = new RectangleEntity();
    body->setWorld(parent->getWorld());
  }

  //getters

  int getIndex() { return index; }
  LogicGate * getParent() { return parent; }

  RectangleEntity * getBody() { return body; }

  //modders

  //virtual

  virtual void select() { body->getColor()->a = 100; }
  virtual void unSelect() { body->getColor()->a = 255; }

  virtual bool getVal() { return 0; }

  virtual void draw() {

    bool val = getVal();

    body->getColor()->r = 255 * val;
    body->getColor()->g = 255 * val;
    body->getColor()->b = 255 * val;

    body->draw();
  }

};

class OutputNode : public AdressNode {

public:
  OutputNode(LogicGate * g, int i) : AdressNode(g, i) {}

  virtual bool getVal() { parent->getOutput(index); }

  virtual void select() { AdressNode::select(); }
  virtual void unSelect() { AdressNode::unSelect(); }
};

class InputNode : public AdressNode {
private:
  OutputNode * conn;

public:
  InputNode(LogicGate * g, int i) : AdressNode(g, i) {
    conn = nullptr;
  }

  OutputNode * getConnection() { return conn; }

  void connect(OutputNode * out) {

    conn = out;

    parent->setInputParent(out->getParent(), index);
    parent->setInputParentOutputIndex(out->getIndex(), index);

    std::cout << "connect" << '\n';

  }

  void deConnect() {

    conn = nullptr;

    parent->setInputParent(nullptr, index);
    parent->setInputParentOutputIndex(-1, index);

    std::cout << "de-connect" << '\n';
  }

  virtual bool getVal() { parent->getInput(index); }

  virtual void select() { AdressNode::select(); }
  virtual void unSelect() { AdressNode::unSelect(); }
};


void setAdressNodes(AdressNode ** nodes, int amtNodes, double size, Vector<double> * start, Vector<double> * end ) {

  double length = start->getDis(*end);

  double gap = length - (size * amtNodes);
  gap /= amtNodes + 1.0;

   Vector<double> * jump = new Vector<double>(0, 0);
   jump->add(*end);
   jump->sub(*start);
   jump->div(length);

   Vector<double> * pos = new Vector<double>(0, 0);
   pos->add(*jump);
   pos->mult(gap);
   pos->add(*start);

   jump->mult((gap + size));

  for (int i = 0; i < amtNodes; i++) {

    RectangleEntity * nodebody = nodes[i]->getBody();
    nodebody->setWidth(size);
    nodebody->setHeight(size);
    nodebody->getPos()->setX(pos->getX());
    nodebody->getPos()->setY(pos->getY());

    pos->add(*jump);
  }

  delete jump, pos;
}
