#include<iostream>
#include"../entity.hh"
#include"../image.hh"

extern "C"{

void e3Callback(entity<image>& ent){
  std::cout << "test" << std::endl;
}

}

