#include"WatorWorld.hh"

WatorWorld::WatorWorld(unsigned int x, unsigned int y){
  this->height = x;
  this->width = y;
  this->universe = new Entity**[x];
  for(int i = 0; i < x; ++i){
    this->universe[i] = new Entity*[y];
  }
}

WatorWorld::WatorWorld(unsigned int x, unsigned int y, Entity*** world):WatorWorld(x, y){
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
 
Entity*** WatorWorld::getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY){
  Entity*** percepts = new Entity**[sX];
  //X and Y radii
  int xR = sX / 2;
  int yR = sY / 2;
  for(int i = 0; i < sY; ++i){
    percepts[i] = new Entity*[sY];
  }
  for(int k = 0; k < sX; ++k){
    for(int l = 0; l < sY; ++l){
      unsigned int x;
      unsigned int y;
      unsigned int xt = cX - (k - xR) % this->height;
      unsigned int yt = cY - (l - yR) % this->width;
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
      percepts[k][l] = this->universe[x][y];
    }
  }
  return percepts;
}

