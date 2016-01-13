#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include"engine.hh"
#include"image.hh"
#include"buffer.hh"
#include"sharedTypes.hh"
#include"physics.hh"

int main(){
  buffer<40, 20> frame;
  physics<image> phys;
  engine eng;
  image img(std::fstream("letterTri.txmg"));
  tri tr(coord(13, 5), coord(10, 8), coord(3, 1));
  entity<image> ent;

  ent.addElement(img);
  phys.addEntity(&ent);

  while(!eng.shouldQuit()){
    phys.checkCollisions();
    frame.clear();
    frame.draw(img, coord(10, 10));
    frame.draw(tr, coord(1, 1), '#');
    frame.display();
  }
  return 0;
}

