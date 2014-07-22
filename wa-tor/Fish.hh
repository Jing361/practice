#ifndef __FISH_H__
#define __FISH_H__

#include"Entity.hh"

class Fish:public Entity{
public:
  Fish();
  Fish(int x, int y);
  Fish(const vec& pos);
  virtual ~Fish();

  char getSym();
  void tick(Entity** percpets[]);
  unsigned int tickAge();
  direction move(Entity** percepts[]);
  Entity* breed();
};

#endif

