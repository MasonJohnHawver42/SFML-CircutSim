#include "../Entity/userMouseCursor.cpp"

void play() {

  WireWorld * world = new WireWorld();

  world->getAssetManager()->loadFile("../assets/Fonts/BarcadeBrawl.ttf");

  BaseLogicGate * test = new BaseLogicGate(new Negator(), world);
  world->addLogicGateType(test);

  BaseLogicGate * test3 = new BaseLogicGate(new AndGate(), world);
  world->addLogicGateType(test3);

  BaseLogicGate * test5 = new BaseLogicGate(new OrGate(), world);
  world->addLogicGateType(test5);

  UserMouseCursor * cursor = new UserMouseCursor(world);
  world->setMouseCursor(cursor);

  Viewer2D * camera = new Viewer2D();
  world->setViewer(camera);

  double fps = 60.0;

  sf::Clock * clock = new sf::Clock();

  while (1) {

    if(clock->getElapsedTime().asSeconds() > 1 / fps) {
      world->updateFrame();
      clock->restart();
    }

    world->update();

  }

  return;
}
