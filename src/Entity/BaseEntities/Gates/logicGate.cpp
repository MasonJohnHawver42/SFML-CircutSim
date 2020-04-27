#include "../rectEntity.cpp"

// connects all the nodes in a node tree / path


class LogicGate : public Entity {
protected:
  string name = string("abc");

  int numOfIns;
  int numOfOuts;

  int * inputs;
  int * outputs;

  LogicGate ** parents;
  int * outputIndexes;

  bool updated;

  void initArrays(int ins, int outs) {
    numOfIns = ins;
    numOfOuts = outs;

    inputs = new int[numOfIns];
    for(int i = 0; i < numOfIns; i++) { inputs[i] = 0; }

    outputs = new int[numOfOuts];
    for(int i = 0; i < numOfOuts; i++) { outputs[i] = 0; }

    parents = new LogicGate*[numOfIns];
    for(int i = 0; i < numOfIns; i++) { parents[i] = nullptr; }

    outputIndexes = new int[numOfIns];
    for(int i = 0; i < numOfIns; i++) { outputIndexes[i] = 0; }
  }


public:
  LogicGate(World *wrld, int ins, int outs) : Entity(wrld) {
    updated = 0;

    initArrays(ins, outs);

  }
  LogicGate(int ins, int outs) : Entity() {
    updated = 0;
    initArrays(ins, outs);
  }
  LogicGate(World *wrld) : Entity(wrld) {
    updated = 0;

    initArrays(10, 10);

  }

  LogicGate() : Entity() {
    updated = 0;

    initArrays(2, 3);
  }

  //getters ---

  string getName() { return name; }

  virtual int getNumOfInputs() { return numOfIns; }
  virtual int getNumOfOutputs() { return numOfOuts; }

  virtual bool getInput(int index) { return inputs[index]; }
  virtual bool getOutput(int index) { return outputs[index]; }

  // get adress

  virtual LogicGate * getInputParent(int index) { return parents[index]; }
  virtual int getInputParentOutputIndex(int index) { return outputIndexes[index]; }

  //setters ---

  virtual void setInput(bool val, int index) { inputs[index] = val; }
  virtual void setOutput(bool val, int index) { outputs[index] = val; }

  virtual void setInputParent(LogicGate * node, int inIndex) { parents[inIndex] = node; }
  virtual void setInputParentOutputIndex(int outIndex, int inIndex) { outputIndexes[inIndex] = outIndex; }

  //moders

  void updateInputs() {
    for (int i = 0; i < getNumOfInputs(); i++) {
      LogicGate * currParent = getInputParent(i);

      if(currParent) {

        int outputIndex = getInputParentOutputIndex(i);

        if (!currParent->isUpdated()) { currParent->updateOutputs(); }
        setInput(currParent->getOutput(outputIndex), i);

      }
      else { setInput(0, i); }

    }
  }

  virtual void calcOutputs() {}

  virtual LogicGate * getCopy() {
    LogicGate * gate = new LogicGate(getWorld(), numOfIns, numOfOuts);
    return gate;
  }

  virtual void updateOutputs() {
    updateInputs();
    calcOutputs();
    updated = 1;
  }

  void clear() {
    updated = 0;
    for (int i = 0; i < getNumOfInputs(); i++) {
      LogicGate * currParent = getInputParent(i);
      if (currParent) {
        if (currParent->isUpdated()) {
          currParent->clear();
        }
      }
    }
  }

  // checkers

  bool isUpdated() { return updated; }

};
