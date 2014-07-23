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

//move by changing position information
void Shark::move(Entity** percepts[]){
}

unsigned int Shark::getRange(){
  return this->seekRange;
}

void Shark::tickAge(){
  ++this->feedTime;
  if(++this->age == this->breedAge){
    this->breed();
  }
  if(this->feedTime == this->starveTime){
    delete this;
  }
}

Entity* Shark::breed(){
  return 0;
}

void Shark::feed(Entity* food){
  this->feedTime = 0;
  delete food;
}

