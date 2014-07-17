#ifndef __FISH_H__
#define __FISH_H__

#include"Entity.hh"

class Fish:public Entity{
public:
  Fish();
  Fish(int x, int y, int z);
  Fish(const vec& pos);

  char getSym();
  void move();
};

#endif

