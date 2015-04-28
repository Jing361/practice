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

enum direction {North, South, East, West};

class Entity:public Renderable{
protected:
  vec position;
  unsigned int age;
  unsigned int breedAge;
public:
  Entity(int x, int y):position(x, y, 0), age(0), breedAge(10){  }
  virtual ~Entity(){  }
  virtual void tick(Entity*** percepts) = 0;
  virtual void move(Entity*** percepts) = 0;
  unsigned int getAge(){ return this->age; }
  virtual void tickAge(){ ++this->age; }
  virtual Entity* breed() = 0;
};

#endif

