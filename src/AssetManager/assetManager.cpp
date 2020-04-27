#include "fontLoader.cpp"


class AssetManager {
private:
  FontLoader * fontLoader;

public:
  AssetManager() {
    FontLoader * fl = new FontLoader();
    fontLoader = fl;
  }

  void loadFile(string fileName) {
    fontLoader->loadAsset(fileName);
    std::cout << "Done Loading File: " << fileName << '\n';
  }

  sf::Font * getFont(string fileName) {
    return fontLoader->getAsset(fileName);
  }

  sf::Font * getFont(int index) {
    return fontLoader->getAsset(index);
  }
};
