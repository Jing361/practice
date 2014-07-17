#ifndef __WATORGAME_H__
#define __WATORGAME_H__

#include"Game.hh"
#include"Fish.hh"
#include"Shark.hh"

class WatorGame:public Game{
public:
  WatorGame();
  ~WatorGame();
  void run();
  void initialize();
  void cleanup();
  void loop();
  void tick();
};

#endif

