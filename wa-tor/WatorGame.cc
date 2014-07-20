#include"WatorGame.hh"

WatorGame::WatorGame(){
  this->initialize();
}

WatorGame::~WatorGame(){
  this->cleanup();
}

void WatorGame::run(){
  this->loop();
}

void WatorGame::initialize(){
  srand(time(NULL));
  this->running = true;
  this->height = 64;
  this->width = 64;
  this->fishFract = .5;
  this->entityCount = (this->height * this->width) / 2;
  this->fishCount = this->entityCount * this->fishFract;
  this->sharkCount = this->entityCount - this->fishCount;

  for(int i = 0; i < 64; ++i){
    for(int j = 0; j < 64; ++j){
      this->world[i][j] = 0;
    }
  }
  for(unsigned int i = 0; i < this->fishCount; ++i){
    unsigned int h, w;
    do{
      h = rand() % this->height;
      w = rand() % this->width;
    } while(this->world[h][w] != 0);
    this->world[h][w] = new Fish(h, w, 0);
  }
  for(unsigned int i = 0; i < this->sharkCount; ++i){
    unsigned int h, w;
    do{
      h = rand() % this->height;
      w = rand() % this->width;
    } while(this->world[h][w] != 0);
    this->world[h][w] = new Shark(h, w, 0);
  }
}

void WatorGame::cleanup(){
}

void WatorGame::loop(){
  while(this->running){
    this->render();
    this->tick();
  }
}

void WatorGame::tick(){
  for(unsigned int i = 0; i < this->height; ++i){
    for(unsigned int j = 0; i < this->width; ++j){
      Entity* ent = this->world[i][j];
      if(ent != 0){
        //Generate percepts for entity
        //I don't like this, do something more OO?
        //TODO:convert world array into a class
        Entity* temp[3][3];
        Entity** percepts[3] = {temp[0],temp[1],temp[2]};
        for(int k = -1; k < 2; ++k){
          for(int l = -1; l < 2; ++l){
            //loop control variable is a modifier to the central cell
            //to generalize: center is half of percept range
            //    modifier is negative half of percept range
            //    up to positive half of percept range
            percepts[1 + k][1 + l] = this->world[i][j];
          }
        }
        //Send percepts for entity to decide new movement
        ent->tick(percepts);
      }
    }
  }
}

void WatorGame::render(){
  for(unsigned int i = 0; i < this->height; ++i){
    for(unsigned int j = 0; j < this->width; ++j){
      if(this->world[i][j] == 0){
        cout << " ";
      } else {
        cout << this->world[i][j]->getSym();
      }
    }
    cout << endl;
  }
  cout << endl;
}

