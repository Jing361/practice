#include"Shark.hh"

//Shark::Shark(int r = 1):Shark(0, 0)
Shark::Shark(int r):Shark(0, 0){
  seekRange = r;
}

Shark::Shark(int x, int y):Entity(x, y){
  sym = 'o';
  seekRange = 1;
  starveTime = 15;
}

Shark::Shark(const vec& pos):Shark(pos.x, pos.y){  }

Shark::~Shark(){
}

char Shark::getSym(){
  return sym;
}

void Shark::tick(Entity*** percepts){
  tickAge();
  move(percepts);
}

//move by changing position information
void Shark::move(Entity*** percepts){
}

unsigned int Shark::getRange(){
  return seekRange;
}

void Shark::tickAge(){
  ++feedTime;
  if(++age == breedAge){
    breed();
  }
  if(feedTime == starveTime){
    delete this;
  }
}

Entity* Shark::breed(){
  return 0;
}

void Shark::feed(Entity* food){
  feedTime = 0;
  delete food;
}

