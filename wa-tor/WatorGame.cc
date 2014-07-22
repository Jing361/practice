#include"WatorGame.hh"

WatorGame::WatorGame():WatorGame(10, 10){  }

WatorGame::WatorGame(unsigned int sX, unsigned int sY):WatorGame(sX, sY, .5){  }

WatorGame::WatorGame(unsigned int sX, unsigned int sY, double fract){
  this->running = true;
  this->height = sX;
  this->width = sY;
  this->fishFract = fract;
  this->entityCount = (this->height * this->width) / 2;
  this->fishCount = this->entityCount * this->fishFract;
  this->sharkCount = this->entityCount - this->fishCount;

  this->initialize();
}

WatorGame::~WatorGame(){
  this->cleanup();
}

void WatorGame::populateWorld(){
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

void WatorGame::run(){
  this->loop();
}

void WatorGame::initialize(){
  srand(time(NULL));

  this->world = new Entity**[this->height];
  for(unsigned int i = 0; i < this->height; ++i){
    this->world[i] = new Entity*[this->width];
  }
  for(unsigned int i = 0; i < this->height; ++i){
    for(unsigned int j = 0; j < this->width; ++j){
      this->world[i][j] = 0;
    }
  }

  this->populateWorld();
}

void WatorGame::cleanup(){
  for(unsigned int i = 0; i < this->height; ++i){
    delete[] this->world[i];
  }
  delete[] this->world;
}

void WatorGame::loop(){
  while(this->running){
    this->render();
    this->tick();
  }
}

void WatorGame::tick(){
  for(unsigned int i = 0; i < this->height; ++i){
    for(unsigned int j = 0; j < this->width; ++j){
      Entity* ent = this->world[i][j];
      if(ent != 0){
        //Generate percepts for entity
        //I don't like this, do something more OO?
        //TODO:convert world array into a class
        Entity* temp[3][3];
        Entity** percepts[3] = {temp[0],temp[1],temp[2]};
        for(int k = 0; k < 3; ++k){
          for(int l = 0; l < 3; ++l){
            int x;
            int y;
            int xt = i - (k - 1) % this->height;
            int yt = j - (l - 1) % this->width;
            //if the xt or yt value is negative, then it can be added, not subtracted
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
            percepts[k][l] = this->world[x][y];
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

