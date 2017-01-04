#include"WatorGame.hh"

WatorGame::WatorGame():WatorGame(10, 10){  }

WatorGame::WatorGame(unsigned int sX, unsigned int sY):WatorGame(sX, sY, .5){  }

WatorGame::WatorGame(unsigned int sX, unsigned int sY, double fract):
  Game(),
  height( sX ),
  width( sY ){
  world = new WatorWorld(height, width);
  fishFract = fract;
  entityCount = (height * width) / 2;
  fishCount = entityCount * fishFract;
  sharkCount = entityCount - fishCount;

  initialize();
}

WatorGame::~WatorGame(){
  cleanup();
}

//Possibly good idea to generate list of entities, and then register them with the game
void WatorGame::populateWorld(){
  for(unsigned int i = 0; i < fishCount; ++i){
    unsigned int h, w;
    do{
      h = rand() % height;
      w = rand() % width;
    } while(world->get(h, w) != 0);
    world->set(h, w, new Fish(h, w));
  }
  for(unsigned int i = 0; i < sharkCount; ++i){
    unsigned int h, w;
    do{
      h = rand() % height;
      w = rand() % width;
    } while(world->get(h, w) != 0);
    world->set(h, w, new Shark(h, w));
  }
}

void WatorGame::run(){
  running = true;
  while(running){
    loop();
  }
}

void WatorGame::initialize(){
  srand(time(NULL));

  world = new WatorWorld(height, width);

  populateWorld();
}

void WatorGame::cleanup(){
  delete world;
}

void WatorGame::loop(){
  render();
  tick();
}

void WatorGame::tick(){
  ++age;
  cout << "game age:" << age << endl;
  for(unsigned int i = 0; i < height; ++i){
    for(unsigned int j = 0; j < width; ++j){
      Entity* ent = world->get(i, j);
      if(ent != 0){
        //Generate percepts for entity
        //I don't like this, do something more OO?
        //TODO:convert world array into a class
        Entity*** percepts;

        percepts = world->getPercepts(i, j, 3, 3);
        //Send percepts for entity to decide new movement
        ent->tick(percepts);
        //update entity's position information here
        delete[] percepts;
      }
    }
  }
}

void WatorGame::render(){
  for(unsigned int i = 0; i < height; ++i){
    for(unsigned int j = 0; j < width; ++j){
      if(world->get(i, j) == 0){
        cout << " ";
      } else {
        cout << world->get(i, j)->getSym();
      }
    }
    cout << endl;
  }
  cout << endl;
}

