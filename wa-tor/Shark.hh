#ifndef __SHARK_H__
#define __SHARK_H__

#include"Entity.hh"

class Shark:public Entity{
protected:
  unsigned int seekRange;
  //Time since feeding
  unsigned int feedTime;
  //Time when starvation occurs
  unsigned int starveTime;
public:
  Shark(int r);
  Shark(int x, int y, int z);
  Shark(const vec& pos);
  virtual ~Shark();

  char getSym();
  void tick();
  direction move(Entity** percepts);
  unsigned int getRange();
  unsigned int tickAge();
  Entity* breed();
  void feed(Entity* food);
};

#endif

