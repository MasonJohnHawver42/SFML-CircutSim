#include "../AssetManager/assetManager.cpp"

class World {
private:

  int id;
  int static next_id;

  Viewer2D * viewer;
  AssetManager * assetManager;

  sf::Clock * masterClock;

  double updateTimeDelta = 0;

public:

  World() {
    viewer = new Viewer2D();
    assetManager = new AssetManager();
    masterClock = new sf::Clock();

    id = next_id;
    next_id++;
  }

  //getters

  int getId() { return id; }

  Viewer2D * getViewer() { return viewer; }

  AssetManager * getAssetManager() { return assetManager; }

  double getUpdateTimeDelta() { return updateTimeDelta; }

  //setters

  void setViewer(Viewer2D * v) { viewer = v; }

  //virtuals

  virtual void start() { masterClock->restart(); }
  virtual void update() { updateTimeDelta = masterClock->restart().asSeconds(); }

  virtual void updateFrame() {}

  virtual bool equal(World other) {
    return (id == other.getId());
  }

};

int World::next_id = 0;
