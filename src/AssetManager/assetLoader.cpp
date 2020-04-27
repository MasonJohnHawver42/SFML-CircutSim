#include "../Viewer/followingVeiwer.cpp"
#include <string>
#include <vector>

string findFileFormat(string file) {
  int index = -1;

  for (int i = 0; i < file.size(); i++) {
    if(file[i] == '.') { index = i + 1; }
  }

  if(index < 0) {
    index = file.size();
  }
  return file.substr(index);
}
//asset class in the future

template <class T>
class AssetLoader {
protected:
  vector<string> * files;
  vector<T*> * assets;

public:
  AssetLoader() {
    files = new vector<string>();
    assets = new vector<T*>();
  }

  virtual string getFileFormat() {
    return string("");
  }

  bool correctFormat(string fileName) {
    string format = findFileFormat(fileName);
    return (format == getFileFormat());
  }

  virtual void loadAsset(string fileName) {
    if(correctFormat(fileName)) {
      files->push_back(fileName);
      //load asset and save into the vector
    }
  }

  T * getAsset(string fileName) {
    for(int i = 0; i < files->size(); i++) {
      if(files->at(i) == fileName) {
        return getAsset(i);
      }
    }
    return nullptr;
  }

  virtual T * getAsset(int index) { return assets->at(index); }
};
