#include "../../World/world.cpp"


class Entity {
private:
  int id;
  static int next_id;

protected:
  World * world;

public:
  Entity() {
    world = nullptr;

    id = next_id;
    next_id++;
  }

  Entity(World * wrld) {
    world = wrld;

    id = next_id;
    next_id++;
  }

  // getters

  int getId() { return id; }

  World * getWorld() { return world; }

  //setters

  void setWorld(World * w) { world = w; }

  // virtual

  virtual void start() {}
  virtual void update(double delta) {}
  virtual void draw() {};

  virtual bool equal(Entity * other) {
    return id == other->getId();
  }

};

int Entity::next_id = 0;
