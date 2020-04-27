#include "../Entity/BaseEntities/mouseCursor.cpp"
#include <vector>

class WireWorld : public World {
protected:
  std::vector<BaseLogicGate *> * logicGates;

  GateSelector * gateSelector;

  MouseCursor * cursor;

public:
  WireWorld() : World() {
    logicGates = new std::vector<BaseLogicGate*>;

    gateSelector = new GateSelector(this);

    cursor = new MouseCursor(this);
  }

  // getters

  int getNumOfLogicGates() { return logicGates->size(); }

  BaseLogicGate * getLogicGate(int index) { return logicGates->at(index); }

  std::vector<BaseLogicGate *> * getLogicGates() { return logicGates; }

  MouseCursor * getCursor() { return cursor; }

  GateSelector * getGateSelector() { return gateSelector; }

  // setters

  void setMouseCursor(MouseCursor * mc) { cursor = mc; }

  //moders

  void addLogicGate(BaseLogicGate * gate) { logicGates->push_back(gate); gate->setWorld(this); }
  void addLogicGateType(BaseLogicGate * gate) { gateSelector->addGate(gate); }

  //other

  virtual void start() {  }
  virtual void update() {
    cursor->update();
    gateSelector->update();
  }

  virtual void updateFrame() {
    World::update();

    sf::RenderWindow * window = getViewer()->getWindow();

    window->clear(sf::Color(50, 50, 50));

    getViewer()->update();

    for(int i = getNumOfLogicGates() - 1; i >= 0; i--) {
      BaseLogicGate * gate = getLogicGate(i);
      gate->draw();
    }

    getGateSelector()->draw();
    getCursor()->draw();

    window->display();
  }

};
