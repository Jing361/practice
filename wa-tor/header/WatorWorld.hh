#ifndef __WATORWORLD_H__
#define __WATORWORLD_H__

#include<vector>

#include"World.hh"
#include"Entity.hh"

class WatorWorld{
public:
  typedef T value_type;

private:
  std::vector<std::vector<Entity> > universe;
  unsigned int height;
  unsigned int width;

public:
  //Specify world size
  //TODO:Implement z-dimension
  WatorWorld(unsigned int x, unsigned int y);
  WatorWorld(unsigned int x, unsigned int y, Entity*** world);
  virtual ~WatorWorld();

  Entity* get(unsigned int x, unsigned int y);
  void set(unsigned int x, unsigned int y, Entity* newEnt);
  Entity*** getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY);
};

#endif

