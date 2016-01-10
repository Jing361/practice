#include<iostream>
#include<string>
#include<chrono>
#include<fstream>
#include"engine.hh"
#include"image.hh"
#include"buffer.hh"
#include"sharedTypes.hh"

int main(){
  buffer<20, 20> frame;
  image img(std::fstream("letterTri.txmg"));
  engine eng;
  tri tr(coord(1, 5), coord(8, 8), coord(3, 1));

  while(!eng.shouldQuit()){
    frame.clear();
    frame.draw(img, coord(10, 10));
    frame.draw(tr, coord(1, 1), '#');
    frame.display();
  }
  return 0;
}

