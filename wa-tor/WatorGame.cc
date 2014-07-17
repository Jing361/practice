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
  this->running = true;
}

void WatorGame::cleanup(){
}

void WatorGame::loop(){
  while(this->running){
    this->tick();
  }
}

void WatorGame::tick(){
}

