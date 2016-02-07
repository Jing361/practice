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

  std::fstream config("map.wld");
  std::string line;
  while(std::getline(config, line)){
    if(line[0] == '#' || line.size() == 0) continue;
    std::stringstream ss(line);
    std::string word;
    std::string name;
    std::map<std::string, image> images;
    std::map<std::string, entity<image>> entities;
    std::map<std::string, tri> triangles;

    ss >> word;
    ss >> name;
    if(word == "img"){
      std::string file;

      ss >> file;
      images[name] = image(std::fstream(file));
    } else if(word == "tri"){
      std::array<coord, 3> arr;

      for(int i = 0; i < 3; ++i){
        std::string x;
        std::string y;

        ss >> x;
        ss >> y;
        arr[i].first = stoi(x);
        arr[i].second = stoi(y);
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
        std::string x;
        std::string y;

        ss >> x;
        ss >> y;
        arr[i].first = stoi(x);
        arr[i].second = stoi(y);
      }
      entities[name].setBoundingBox(std::pair<coord, coord>(arr[0], arr[1]));
    } else if(word == "stp"){
      std::string x;
      std::string y;

      ss >> x;
      ss >> y;
      entities[name].getPosition() = vec2(stod(x), stod(y));
    } else if(word == "stv"){
      std::string x;
      std::string y;

      ss >> x;
      ss >> y;
      entities[name].getVelocity() = vec2(stod(x), stod(y));
    } else if(word == "sta"){
      std::string x;
      std::string y;

      ss >> x;
      ss >> y;
      entities[name].getAcceleration() = vec2(stod(x), stod(y));
    }
  }

  image img1(std::fstream("letterTri.txmg"));
  image img2(std::fstream("letterRect.txmg"));
  tri tr(coord(13, 5), coord(10, 8), coord(3, 1));
  entity<image> ent1;
  entity<image> ent2;
  std::clock_t last;

  ent1.setBoundingBox(std::pair<coord, coord>(coord(0, 0), coord(3, 3)));
  ent2.setBoundingBox(std::pair<coord, coord>(coord(0, 0), coord(3, 3)));
  ent1.addElement(img1);
  ent2.addElement(img2);
  ent1.getPosition() = vec2(10, 10);
  ent2.getPosition() = vec2(5, 5);
  ent2.getVelocity() += vec2(1, 1);
  phys.addEntity("one", &ent1);
  phys.addEntity("two", &ent2);
  last = clock();

  while(!eng.shouldQuit()){
    std::clock_t diff = clock() - last;
    phys.checkCollisions();
    frame.clear();
    frame.draw(ent1);
    frame.draw(ent2);
    phys.tick(diff);
    //frame.draw(tr, coord(1, 1), '#');
    frame.display();
  }
  return 0;
}

