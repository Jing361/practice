#include"Shark.hh"

Shark::Shark(int r = 1):Shark(0, 0){
  this->seekRange = r;
}

Shark::Shark(int x, int y):Entity(x, y){
  this->sym = 'o';
  this->seekRange = 1;
  this->starveTime = 15;
}

Shark::Shark(const vec& pos):Shark(pos.x, pos.y){  }

Shark::~Shark(){
}

char Shark::getSym(){
  return this->sym;
}

void Shark::tick(Entity** percepts[]){
  this->tickAge();
  this->move(percepts);
}

direction Shark::move(Entity** percepts[]){
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
  return 0;
}

void Shark::feed(Entity* food){
  this->feedTime = 0;
  delete food;
}

