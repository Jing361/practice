#include"Fish.hh"

Fish::Fish():Fish(0, 0, 0){  }

Fish::Fish(int x, int y, int z):Entity(x, y, z){
  this->sym = '.';
}

Fish::Fish(vec pos):Fish(pos.x, pos.y, pos.z){  }

