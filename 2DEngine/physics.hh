#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include"entity.hh"

class physics{
private:
  std::vector<entity&> m_entity;

public:
  void addEntity(entity& ent);
  void checkCollisions();
};

#endif

