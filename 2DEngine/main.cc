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
  image img1(std::fstream("letterTri.txmg"));
  image img2(std::fstream("letterRect.txmg"));
  tri tr(coord(13, 5), coord(10, 8), coord(3, 1));
  entity<image> ent1;
  entity<image> ent2;

  ent1.setBoundingBox(std::pair<coord, coord>(coord(0, 0), coord(3, 3)));
  ent2.setBoundingBox(std::pair<coord, coord>(coord(0, 0), coord(3, 3)));
  ent1.addElement(img1);
  ent2.addElement(img2);
  phys.addEntity("one", &ent1);
  phys.addEntity("two", &ent2);

  while(!eng.shouldQuit()){
    phys.checkCollisions();
    frame.clear();
    frame.draw(img1, coord(10, 10));
    frame.draw(img2, coord(5, 5));
    //frame.draw(tr, coord(1, 1), '#');
    frame.display();
  }
  return 0;
}

