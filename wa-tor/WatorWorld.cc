#include"WatorWorld.hh"

WatorWorld::WatorWorld(unsigned int x, unsigned int y){
  height = x;
  width = y;

  universe = new Entity**[height];
  for(unsigned int i = 0; i < height; ++i){
    universe[i] = new Entity*[width];
  }
}

WatorWorld::WatorWorld(unsigned int x, unsigned int y, Entity*** world):WatorWorld(x, y){
  for(unsigned int i = 0; i < x; ++i){
    for(unsigned int j = 0; j < y; ++j){
      universe[i][j] = world[i][j];
    }
  }
}

WatorWorld::~WatorWorld(){
  for(unsigned int i = 0; i < height; ++i){
    delete[] universe[i];
  }
  delete[] universe;
}

Entity* WatorWorld::get(unsigned int x, unsigned int y){
  return universe[x][y];
}
 
void WatorWorld::set(unsigned int x, unsigned int y, Entity* newEnt){
  universe[x][y] = newEnt;
}
 
Entity*** WatorWorld::getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY){
  //X and Y radii
  int xR = sX / 2;
  int yR = sY / 2;

  Entity*** percepts = new Entity**[sX];
  for(unsigned int i = 0; i < sY; ++i){
    percepts[i] = new Entity*[sY];
  }

  for(unsigned int k = 0; k < sX; ++k){
    for(unsigned int l = 0; l < sY; ++l){
      int x;
      int y;
      int xt = cX - (k - xR) % height;
      int yt = cY - (l - yR) % width;
      //Account for negative world indexes
      if(xt < 0){
        x = height + xt;
      } else {
        x = xt;
      }
      if(yt < 0){
        y = width + yt;
      } else {
        y = yt;
      }

      //loop control variable is a modifier to the central cell
      //to generalize: center is half of percept range
      //    modifier is negative half of percept range
      //    up to positive half of percept range
      percepts[k][l] = universe[x][y];
    }
  }
  return percepts;
}

