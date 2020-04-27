#include "andGate.cpp"

class OrGate : public LogicGate {
public:
  OrGate() : LogicGate(2, 1) {
    name = string("OR\nGate");
  }
  OrGate(World * wrld) : LogicGate(wrld, 2, 1) {
    name = string("OR\nGate");
  }

  virtual void calcOutputs() {
    outputs[0] = inputs[0] || inputs[1];
  }

  virtual LogicGate * getCopy() {
    LogicGate * gate = new OrGate(getWorld());
    return gate;
  }
};
