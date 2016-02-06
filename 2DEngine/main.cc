#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include<ctime>
#include"engine.hh"
#include"image.hh"
#include"buffer.hh"
#include"sharedTypes.hh"
#include"physics.hh"

int main(){
  buffer<40, 20> frame;
  physics<image> phys;
  engine eng;
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

