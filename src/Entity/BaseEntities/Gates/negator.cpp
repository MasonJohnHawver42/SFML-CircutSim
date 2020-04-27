#include "orGate.cpp"

class Negator : public LogicGate {
public:
  Negator() : LogicGate(1, 1) {
    name = string("Not\nGate");
  }
  Negator(World * wrld) : LogicGate(wrld, 1, 1) {
    name = string("Not\nGate");
  }

  virtual void calcOutputs() {
    outputs[0] = !inputs[0];
  }

  virtual LogicGate * getCopy() {
    LogicGate * gate = new Negator(getWorld());
    return gate;
  }
};
