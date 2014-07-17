#ifndef __ENTITY_H__
#define __ENTITY_H__

#include"Renderable.hh"

class vec{
public:
  int x, y, z;
  vec():x(0),
        y(0),
        z(0){ }
  vec(int x, int y, int z):x(x),
                           y(y),
                           z(z){}
  vec(const vec& vect):x(vect.x),
                y(vect.y),
                z(vect.z){  }
};

class Entity:public Renderable{
protected:
  vec position;
public:
  Entity(int x, int y, int z):position(x, y, z){  }
  virtual void move() = 0;
};

#endif

