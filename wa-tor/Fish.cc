#include"Fish.hh"

Fish::Fish():Fish(0, 0, 0){  }

Fish::Fish(int x, int y, int z):Entity(x, y, z){
  this->sym = '.';
}

Fish::Fish(const vec& pos):Fish(pos.x, pos.y, pos.z){  }

char Fish::getSym(){
  return this->sym;
}

void Fish::tick(){
}

direction Fish::move(Entity** percepts){
  return North;
}

Entity* Fish::breed(){
  return new Fish;
}

