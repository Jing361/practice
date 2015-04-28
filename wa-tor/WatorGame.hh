#ifndef __WATORGAME_H__
#define __WATORGAME_H__

#include<cstdlib>
#include<time.h>
#include<iostream>
#include"Game.hh"
#include"Fish.hh"
#include"Shark.hh"
#include"WatorWorld.hh"
using std::cout;
using std::endl;

//TODO:Update to MVC paradigm
//TODO:Use an entity list to iterate instead of iterating whole world?
class WatorGame:public Game{
private:
  void populateWorld();
protected:
  unsigned int entityCount;
  unsigned int height, width;
  double fishFract;
  unsigned int fishCount, sharkCount;
//  Entity*** world;
  WatorWorld* world;
public:
  WatorGame();
  WatorGame(unsigned int sX, unsigned int sY);
  WatorGame(unsigned int sX, unsigned int sY, double fract);
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

