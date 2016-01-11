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
  image img(std::fstream("letterTri.txmg"));
  engine eng;
  physics phys;
  tri tr(coord(1, 5), coord(8, 8), coord(3, 1));

  while(!eng.shouldQuit()){
    frame.clear();
    frame.draw(img, coord(10, 10));
    frame.draw(tr, coord(1, 1), '#');
    frame.display();
  }
  return 0;
}

