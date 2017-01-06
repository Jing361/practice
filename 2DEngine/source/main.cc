#include<map>
#include<functional>
#include<iostream>
#include<string>
#include<sstream>

#include"entity.hh"
#include"image.hh"
#include"sharedTypes.hh"
#include"physics.hh"
#include"graphics.hh"

int main(int argc, char** argv){
  if(argc != 2){
    return 1;
  }

  physics<image> phys;
  graphics<80, 40> gfx;
  gfx.m_configCallbacks["phys"] = [&](std::string name, std::string line,
                                      std::map<std::string, image>& images,
                                      std::map<std::string, entity<image>>& entities,
                                      std::map<std::string, tri>& tris){
    (void) images;
    (void) tris;

    std::stringstream ss(line);
    std::string alias;

    ss >> alias;
    ss >> alias;
    ss >> alias;

    phys.addEntity(alias, &entities[name]);
  };
  gfx.loadConfig(argv[1]);

  phys.setDamping(.6);
  gfx.m_tickCallbacks.push_back([&](double diff){
    phys.checkCollisions();
    phys.tick(diff);
  });

  gfx.run();

  return 0;
}

