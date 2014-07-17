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
      if(this->world[i][j] != 0){
//        this->world[i][j]->move();
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

