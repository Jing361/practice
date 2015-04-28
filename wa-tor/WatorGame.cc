#include"WatorGame.hh"

WatorGame::WatorGame():WatorGame(10, 10){  }

WatorGame::WatorGame(unsigned int sX, unsigned int sY):WatorGame(sX, sY, .5){  }

WatorGame::WatorGame(unsigned int sX, unsigned int sY, double fract){
  this->running = true;
  this->height = sX;
  this->width = sY;
  this->world = new WatorWorld(this->height, this->width);
  this->fishFract = fract;
  this->entityCount = (this->height * this->width) / 2;
  this->fishCount = this->entityCount * this->fishFract;
  this->sharkCount = this->entityCount - this->fishCount;

  this->initialize();
}

WatorGame::~WatorGame(){
  this->cleanup();
}

//Possibly good idea to generate list of entities, and then register them with the game
void WatorGame::populateWorld(){
  for(unsigned int i = 0; i < this->fishCount; ++i){
    unsigned int h, w;
    do{
      h = rand() % this->height;
      w = rand() % this->width;
    } while(this->world->get(h, w) != 0);
    this->world->set(h, w, new Fish(h, w));
  }
  for(unsigned int i = 0; i < this->sharkCount; ++i){
    unsigned int h, w;
    do{
      h = rand() % this->height;
      w = rand() % this->width;
    } while(this->world->get(h, w) != 0);
    this->world->set(h, w, new Shark(h, w));
  }
}

void WatorGame::run(){
  this->loop();
}

void WatorGame::initialize(){
  srand(time(NULL));

  this->world = new WatorWorld(this->height, this->width);

  this->populateWorld();
}

void WatorGame::cleanup(){
  delete this->world;
}

void WatorGame::loop(){
  while(this->running){
    this->render();
    this->tick();
  }
}

void WatorGame::tick(){
  ++this->age;
  cout << "game age:" << this->age << endl;
  for(unsigned int i = 0; i < this->height; ++i){
    for(unsigned int j = 0; j < this->width; ++j){
      Entity* ent = this->world->get(i, j);
      if(ent != 0){
        //Generate percepts for entity
        //I don't like this, do something more OO?
        //TODO:convert world array into a class
        Entity*** percepts;

        //percepts = this->world->getPercepts();
        //Send percepts for entity to decide new movement
        ent->tick(percepts);
        //update entity's position information here
      }
    }
  }
}

void WatorGame::render(){
  for(unsigned int i = 0; i < this->height; ++i){
    for(unsigned int j = 0; j < this->width; ++j){
      if(this->world->get(i, j) == 0){
        cout << " ";
      } else {
        cout << this->world->get(i, j)->getSym();
      }
    }
    cout << endl;
  }
  cout << endl;
}

