#include"Fish.hh"

Fish::Fish():Fish(0, 0, 0){  }

Fish::Fish(int x, int y, int z):Entity(x, y, z){
  this->sym = '.';
}

Fish::Fish(const vec& pos):Fish(pos.x, pos.y, pos.z){  }

char Fish::getSym(){
  return this->sym;
}

Fish::~Fish(){
}

void Fish::tick(Entity** percepts[]){
  this->tickAge();
  this->move(percepts);
}

unsigned int Fish::tickAge(){
  unsigned int ag = (++this->age);
  if(ag == this->breedAge){
    this->breed();
  }
  return ag;
}

direction Fish::move(Entity** percepts[]){
  return North;
}

Entity* Fish::breed(){
  return new Fish;
}

