#include<iostream>
#include"../entity.hh"
#include"../image.hh"

extern "C"{

void e3commaCallback(entity<image>& ent){
  ent.getVelocity().second -= 1;
}

void e3oCallback(entity<image>& ent){
  ent.getVelocity().second += 1;
}
void e3eCallback(entity<image>& ent){
  ent.getVelocity().first += 1;
}

void e3aCallback(entity<image>& ent){
  ent.getVelocity().first -= 1;
}

}

