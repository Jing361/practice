#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include"entity.hh"

template<class T>
class physics{
private:
  std::vector<entity<T>*> m_entity;

public:
  void addEntity(entity<T>& ent);
  void checkCollisions();
};

#endif

