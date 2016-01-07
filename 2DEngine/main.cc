#include<string>
#include"image.hh"
#include"buffer.hh"

int main(){
  buffer<20, 20> frame;
  std::string str("A\n"
                  "BB\n"
                  "CCC\n");
  image img(str);

  for(unsigned int i = 0; i < 5; ++i){
    frame.clear();
    frame.render(img, coord(10 + i, 10));
    frame.display();
  }
  return 0;
}

