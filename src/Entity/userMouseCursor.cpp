#include"worldEntity.cpp"

class UserMouseCursor : public MouseCursor, public WorldEntity  {
private:
  int selectedGate;

  InputNode * selectedInput = nullptr;

  bool clicked = 0;

  bool move = 0;
  bool resize = 0;

public:
  UserMouseCursor(WireWorld * wrld) : MouseCursor(wrld),  WorldEntity(wrld) {
    selectedGate = -1;
  }

  int getSelectedLogicGate() {
    for(int i = 0; i < basicWorld->getNumOfLogicGates(); i++) {
      BaseLogicGate * gate = basicWorld->getLogicGate(i);

      if(gate->isInside(pos)) {
        return i;
      }
    }

    return -1;
  }

  virtual void update() {
    Vector<double> * diff = new Vector<double>(pos->getX(), pos->getY());


    int currGate = getSelectedLogicGate();

    MouseCursor::update();
    diff->sub(*pos);

    bool inGS = basicWorld->getGateSelector()->getBody()->isInside(pos);

    if(inGS) {
      int i = basicWorld->getGateSelector()->getGate(pos);
      if(i != -1) {
        if(selectedGate == -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          BaseLogicGate * newGate = basicWorld->getGateSelector()->getGateCopy(i);
          basicWorld->addLogicGate(newGate);
          newGate->select();
          move = 1;

          selectedGate = basicWorld->getNumOfLogicGates() - 1;
        }
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        basicWorld->getGateSelector()->slide(.01, world->getUpdateTimeDelta());
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        basicWorld->getGateSelector()->slide(-.01, world->getUpdateTimeDelta());
      }
    }
    else {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        world->getViewer()->zoom(1.001, world->getUpdateTimeDelta());
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        world->getViewer()->zoom(1 - .001, world->getUpdateTimeDelta());
      }
    }

    if (currGate == -1 && !inGS) {
      if(!clicked && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        clicked = 1;
      }
    }

    if(clicked) {
      pos->add(*diff);
      getWorld()->getViewer()->getPos()->add(*diff);
    }

    if(clicked && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      clicked = 0;
    }

    if (currGate != -1 && !inGS) {

      BaseLogicGate * gateWrapper = basicWorld->getLogicGate(currGate);
      LogicGate * gate = gateWrapper->getGate();
      RectangleEntity * body = gateWrapper->getBody();

      if(body->isInside(pos)) {

        color->r = 255;

        double dis = (abs((body->getPos()->getX() + body->getWidth()) - pos->getX()) / body->getWidth()) + (abs((body->getPos()->getY() + body->getHeight()) - pos->getY()) / body->getHeight());
        if(dis < .25) { color->g = 255; }
        else { color->g = 0; }

        //select gate

        if (selectedGate == -1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          selectedGate = currGate;
          gateWrapper->select();

          std::vector<BaseLogicGate *> * gates = basicWorld->getLogicGates();
          gates->erase(gates->begin() + selectedGate, gates->begin() + selectedGate + 1);
          //gates->insert(gates->begin(), gateWrapper);
          gates->push_back(gateWrapper);

          selectedGate = gates->size() - 1;


          if(dis < .25) { resize = 1; }
          else { move = 1; }
        }

        //update gate

        if (selectedGate == -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          if(!gate->isUpdated()) { gate->updateOutputs();
          std::cout << "gate updated" << '\n'; }
        }

        //clear gate

        else if (selectedGate == -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
          if(gate->isUpdated()) { gate->clear();
          std::cout << "gate cleared" << '\n'; }
        }
      }
      //reset colors
      else { color->r = 0; color->g = 0; }

      //select input

      if (pos->getX() - body->getPos()->getX() < 0) {
        InputNode * in = gateWrapper->getInput(pos);

        if(in) {
          if (!selectedInput && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            selectedInput = in;
            selectedInput->select();
            //std::cout << "selectedInput" << selectedInput->getIndex() << '\n';
          }
        }
      }

      //select output
      else if (pos->getX() - body->getPos()->getX() > body->getWidth()) {
        OutputNode * out = gateWrapper->getOutput(pos);

        if(out) {
          if (selectedInput && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            selectedInput->connect(out);
            selectedInput->unSelect();
            selectedInput = nullptr;
          }
        }
      }
    }

    //unconect selected input

    else{
      if (selectedInput && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        selectedInput->deConnect();
        selectedInput->unSelect();
        selectedInput = nullptr;
      }
    }

    //unselect gate

    if (selectedGate != -1  && sf::Mouse::isButtonPressed(sf::Mouse::Right) ) {
      basicWorld->getLogicGate(selectedGate)->unSelect();
      selectedGate = -1;

      move = 0;
      resize = 0;
    }

    //unselect input

    if (selectedInput && sf::Mouse::isButtonPressed(sf::Mouse::Right) ) {
      selectedInput->unSelect();
      selectedInput = nullptr;
    }

    //move gate

    if(selectedGate != -1 && move) {
      basicWorld->getLogicGate(selectedGate)->move(diff);

    }

    //resize gate

    else if(selectedGate != -1 && resize) {
      basicWorld->getLogicGate(selectedGate)->resize(pos);
    }
    delete diff;
  }

};
