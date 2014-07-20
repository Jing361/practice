#ifndef __WATORGAME_H__
#define __WATORGAME_H__

#include<cstdlib>
#include<time.h>
#include<iostream>
#include"Game.hh"
#include"Fish.hh"
#include"Shark.hh"
using std::cout;
using std::endl;

//TODO:Update to MVC paradigm
class WatorGame:public Game{
protected:
  unsigned int entityCount;
  unsigned int height, width;
  double fishFract;
  unsigned int fishCount, sharkCount;
  Entity* world[64][64];
public:
  WatorGame();
  ~WatorGame();
  void run();
  void initialize();
  void cleanup();
  void loop();
  //Entity updates
  void tick();
  //Render everything
  void render();
};

#endif

