#ifndef __WATORWORLD_H__
#define __WATORWORLD_H__

#include"World.hh"
#include"Entity.hh"

class WatorWorld:public World<Entity*>{
public:
  //Specify world size
  //Z dimension defaults to 0
  //TODO:Make z-dimension work
  WatorWorld(unsigned int x, unsigned int y);
  WatorWorld(unsigned int x, unsigned int y, Entity** world);

  Entity* get(unsigned int x, unsigned int y);
  void set(unsigned int x, unsigned int y, Entity* newEnt);
  Entity** getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY);
};

#endif

