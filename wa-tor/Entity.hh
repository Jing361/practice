#include"Renderable.hh"

typedef struct vec{
  int x, y, z;
}vec;

class Entity:public Renderable{
protected:
  vec position;
};
