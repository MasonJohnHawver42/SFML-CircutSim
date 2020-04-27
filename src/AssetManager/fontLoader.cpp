#include "assetLoader.cpp"


class FontLoader : public AssetLoader<sf::Font> {
private:
  static string fileFormat;

public:
 FontLoader() : AssetLoader() {}

 virtual string getFileFormat() {
   return fileFormat;
 }

 virtual void loadAsset(string fileName) {
   if(correctFormat(fileName)) {
     files->push_back(fileName);

     sf::Font * font = new sf::Font();
     font->loadFromFile(fileName);

     assets->push_back(font);
   }
 }
};
string FontLoader::fileFormat = string("ttf");
