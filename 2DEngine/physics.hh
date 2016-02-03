#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<map>
#include<string>
#include"entity.hh"

template<class T>
class physics{
private:
  std::map<std::string, entity<T>*> m_entity;

public:
  bool checkCollision(const std::pair<coord, coord>& box1, const std::pair<coord, coord>& box2);
  void addEntity(std::string name, entity<T>* ent);
  void checkCollisions();
};

#include"physics.cc"

#endif

