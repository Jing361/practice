#include<sstream>
#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include<ctime>
#include<vector>
#include<map>
#include"engine.hh"
#include"image.hh"
#include"buffer.hh"
#include"sharedTypes.hh"
#include"physics.hh"

int main(){
  buffer<40, 20> frame;
  physics<image> phys;
  engine eng;
  std::map<std::string, image> images;
  std::map<std::string, entity<image>> entities;
  std::map<std::string, tri> triangles;

  std::fstream config("map.wld");
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
      images[name] = image(std::fstream(file));
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
      triangles[name] = tr;
    } else if(word == "ent"){
      std::string img;
      entity<image> ent;

      ss >> img;
      ent.addElement(images[img]);
      entities[name] = ent;
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
      entities[name].setBoundingBox(std::pair<coord, coord>(arr[0], arr[1]));
    } else if(word == "stp"){
      double x;
      double y;

      ss >> x;
      ss >> y;
      entities[name].getPosition() = vec2(x, y);
    } else if(word == "stv"){
      double x;
      double y;

      ss >> x;
      ss >> y;
      entities[name].getVelocity() = vec2(x, y);
    } else if(word == "sta"){
      double x;
      double y;

      ss >> x;
      ss >> y;
      entities[name].getAcceleration() = vec2(x, y);
    } else if(word == "stm"){
      double val;

      ss >> val;
      entities[name].getMass() = val;
    } else if(word == "phys"){
      std::string alias;

      ss >> alias;
      phys.addEntity(alias, &entities[name]);
    }
  }

  std::clock_t last = clock();

  while(!eng.shouldQuit()){
    std::clock_t diff = clock() - last;
    phys.checkCollisions();
    frame.clear();
    for(auto it:entities){
      frame.draw(it.second);
    }
    phys.tick(diff);
    frame.display();
  }
  return 0;
}

