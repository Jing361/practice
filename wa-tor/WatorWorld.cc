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
 
Entity*** getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY){
  Entity*** percepts = new Entity**[sX];
  for(int i = 0; i < sY; ++i){
    percepts[i] = new Entity*[sY];
  }
  for(int k = cX - (sX / 2); k < (cX + (sX / 2)); ++k){
    for(int l = cY - (sY / 2); l < (cY + (sY / 2)); ++l){
      unsigned int x;
      unsigned int y;
      unsigned int xt = (1 + k) % this->height;
      unsigned int yt = (1 + l) % this->width;
      //Account for negative world indexes
      if(xt < 0){
        x = this->height + xt;
      } else {
        x = xt;
      }
      if(yt < 0){
        y = this->width + yt;
      } else {
        y = yt;
      }
      //loop control variable is a modifier to the central cell
      //to generalize: center is half of percept range
      //    modifier is negative half of percept range
      //    up to positive half of percept range
      percepts[x][y] = this->universe[i][j];
    }
  }
}

