#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<map>
#include<string>
#include"entity.hh"

template<class T>
class physics{
private:
  std::map<std::string, entity<T>*> m_entity;
  double m_dampingForce = 0.0;

public:
  bool checkCollision(const std::pair<coord, coord>& box1, const std::pair<coord, coord>& box2);
  void addEntity(std::string name, entity<T>* ent);
  void checkCollisions();
  void setDamping(double f);
  void tick(double diff);
};

#include"physics.cc"

#endif

