#include"Fish.hh"

Fish::Fish():Fish(0, 0){  }

Fish::Fish(int x, int y):Entity(x, y){
  this->sym = '.';
}

Fish::Fish(const vec& pos):Fish(pos.x, pos.y){  }

char Fish::getSym(){
  return this->sym;
}

Fish::~Fish(){
}

void Fish::tick(Entity*** percepts){
  this->tickAge();
  this->move(percepts);
}

void Fish::tickAge(){
  if(++this->age == this->breedAge){
    this->breed();
  }
}

//move by changing position information
void Fish::move(Entity*** percepts){
}

Entity* Fish::breed(){
  return new Fish;
}

