#include"WatorWorld.hh"

WatorWorld::WatorWorld(unsigned int x, unsigned int y){
  this->universe = new Entity**[x];
  for(int i = 0; i < x; ++i){
    this->universe[i] = new Entity*[y];
  }
}

WatorWorld::WatorWorld(unsigned int x, unsigned int y, Entity** world):WatorWorld(x, y){
  for(int i = 0; i < x; ++i){
    for(int j = 0; j < y; ++j){
      this->universe[i][j] = world[i][j];
    }
  }
}

Entity* WatorWorld::get(unsigned int x, unsigned int y){
  return this->universe[x][y];
}
 
void WatorWorld::set(unsigned int x, unsigned int y, Entity* newEnt){
  this->universe[x][y] = newEnt;
}
 
Entity** getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY){
}

