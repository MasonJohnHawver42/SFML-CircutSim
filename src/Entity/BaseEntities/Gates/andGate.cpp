#include"logicGate.cpp"

class AndGate : public LogicGate {
public:
  AndGate() : LogicGate(2, 1) {
    name = string("And\nGate");
  }

  AndGate(World * wrld) : LogicGate(wrld, 2, 1) {
    name = string("And\nGate");
  }

  virtual void calcOutputs() {
    outputs[0] = inputs[0] && inputs[1];
  }

  virtual LogicGate * getCopy() {
    LogicGate * gate = new AndGate(getWorld());
    return gate;
  }
};
