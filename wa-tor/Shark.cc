#include"Shark.hh"

Shark::Shark(int r = 1):Shark(0, 0, 0){
  this->seekRange = r;
}

Shark::Shark(int x, int y, int z):Entity(x, y, z){
  this->sym = 'o';
  this->seekRange = 1;
  this->starveTime = 15;
}

Shark::Shark(const vec& pos):Shark(pos.x, pos.y, pos.z){  }

Shark::~Shark(){
}

char Shark::getSym(){
  return this->sym;
}

void Shark::tick(){
}

direction Shark::move(Entity** percepts){
  return North;
}

unsigned int Shark::getRange(){
  return this->seekRange;
}

unsigned int Shark::tickAge(){
  unsigned int ag = (++this->age);
  ++this->feedTime;
  if(ag == this->breedAge){
    this->breed();
  }
  if(this->feedTime == this->starveTime){
    delete this;
  }
  return ag;
}

Entity* Shark::breed(){
}

void Shark::feed(Entity* food){
  delete food;
}
