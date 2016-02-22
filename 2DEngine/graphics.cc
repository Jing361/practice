#include<dlfcn.h>
#include<sstream>
#include<fstream>
#include"graphics.hh"
#include"sharedTypes.hh"

template<unsigned int X, unsigned int Y>
graphics<X, Y>::~graphics(){
  for(auto it:m_libs){
    dlclose(it);
  }
}

template<unsigned int X, unsigned int Y>
void graphics<X, Y>::loadConfig(std::string configFile){
  void* handle;
  std::fstream config(configFile);
  std::string line;

  while(std::getline(config, line)){
    if(line[0] == '#' || line.size() == 0) continue;
    std::stringstream ss(line);
    std::string word;
    std::string name;

    ss >> word;
    ss >> name;
    if(word == "img"){
      std::string file;

      ss >> file;
      m_images[name] = image(std::fstream(file));
    } else if(word == "tri"){
      std::array<coord, 3> arr;

      for(int i = 0; i < 3; ++i){
        int x;
        int y;

        ss >> x;
        ss >> y;
        arr[i].first = x;
        arr[i].second = y;
      }

      tri tr(coord(arr[0].first, arr[0].second), coord(arr[0].first, arr[0].second), coord(arr[0].first, arr[0].second));
      m_triangles[name] = tr;
    } else if(word == "ent"){
      std::string img;
      entity<image> ent;

      ss >> img;
      ent.addElement(m_images[img]);
      m_entities[name] = ent;
    } else if(word == "stbb"){
      std::array<coord, 2> arr;

      for(int i = 0; i < 2; ++i){
        int x;
        int y;

        ss >> x;
        ss >> y;
        arr[i].first = x;
        arr[i].second = y;
      }
      m_entities[name].setBoundingBox(std::pair<coord, coord>(arr[0], arr[1]));
    } else if(word == "stp"){
      double x;
      double y;

      ss >> x;
      ss >> y;
      m_entities[name].getPosition() = vec2(x, y);
    } else if(word == "stv"){
      double x;
      double y;

      ss >> x;
      ss >> y;
      m_entities[name].getVelocity() = vec2(x, y);
    } else if(word == "sta"){
      double x;
      double y;

      ss >> x;
      ss >> y;
      m_entities[name].getAcceleration() = vec2(x, y);
    } else if(word == "stm"){
      double val;

      ss >> val;
      m_entities[name].getMass() = val;
    } else if(word == "lib"){
      handle = dlopen(name.data(), RTLD_LAZY);
      if(!handle){
        throw libraryNotFoundException(name);
      }
      m_libs.push_back(handle);
    } else if(word == "cbk"){
      std::string fn;
      char key;
      char* error;

      ss >> key;
      ss >> fn;
      auto tmp = (void(*)(entity<image>&))dlsym(handle, fn.data());
      if((error = dlerror()) != 0){
        throw badLibFuncReferenceException(fn);
      }
      auto callback = std::bind(tmp, std::ref(m_entities[name]));
      m_eng.registerCallback(key, callback);
    } else {
      try{
        m_configCallbacks.at(word)(name, line, m_images, m_entities, m_triangles);
      } catch(std::out_of_range& e){
        throw unrecognizedKeywordException(word, configFile);
      }
    }
  }
}
template<unsigned int X, unsigned int Y>
void graphics<X, Y>::tick(double diff){
  m_frame.clear();
  for(auto it:m_entities){
    m_frame.draw(it.second);
  }
  m_frame.display();
  for(auto it:m_tickCallbacks){
    it(diff);
  }
}

template<unsigned int X, unsigned int Y>
void graphics<X, Y>::run(){
  std::clock_t last = clock();

  while(!m_eng.shouldQuit()){
    std::clock_t now = clock();
    std::clock_t diff = now - last;
    last = now;
    tick(diff);
  }
}

