#ifndef __SHARK_H__
#define __SHARK_H__

#include"Entity.hh"

class Shark:public Entity{
protected:
  unsigned int seekRange;
public:
  Shark();
  Shark(int x, int y, int z);
  Shark(const vec& pos);

  void move();
};

#endif

