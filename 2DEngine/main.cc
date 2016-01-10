#include<iostream>
#include<string>
#include<chrono>
#include"engine.hh"
#include"image.hh"
#include"buffer.hh"
#include"sharedTypes.hh"

int main(){
  buffer<20, 20> frame;
  std::string str("A\n"
                  "BB\n"
                  "CCC\n");
  image img(str);
  engine eng;
  coord v1(1, 5);
  coord v2(8, 8);
  coord v3(3, 1);
  tri tr(v1, v2, v3);

  while(!eng.shouldQuit()){
    frame.clear();
    frame.draw(img, coord(10, 10));
    frame.draw(tr, coord(3, 5), '#');
    frame.display();
  }
  return 0;
}

