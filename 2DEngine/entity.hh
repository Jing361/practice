#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include<tuple>
#include"sharedTypes.hh"
#include"buffer.hh"

template<class T>
class entity{
private:
  std::vector<std::pair<T, coord>> m_image;
  std::pair<coord, coord> m_box;
  vec2 m_pos;
  vec2 m_vel;
  vec2 m_acc;

public:
  entity(vec2 pos = { 0, 0}, vec2 vel = { 0, 0}, vec2 acc = { 0, 0});

  void addElement(T t, coord cor = coord(0, 0));
  template<unsigned int X, unsigned int Y>
  void draw(buffer<X, Y>& frame);
  template<class U>
  void collide(entity<U> ent);
  std::pair<coord, coord> getBoundingBox();
  void setBoundingBox(std::pair<coord, coord> box);
  vec2& getPosition();
  vec2& getVelocity();
  vec2& getAcceleration();
  void tick(double diff);
};

#include"entity.cc"

#endif

