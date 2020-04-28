#include "../World/wireWorld.cpp"

class WorldEntity {
protected:
  WireWorld * basicWorld;

public:
  WorldEntity(WireWorld * wrld) { basicWorld = wrld; }

  //getters

  WireWorld * getBasicWorld() { return basicWorld; }

  //setters

  virtual void setBasicWorld(WireWorld * wrld) {
    basicWorld = wrld;
  }
};
