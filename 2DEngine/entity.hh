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

public:
  coord m_coord;

  void addElement(T t, coord cor = coord(0, 0));
  void draw(buffer& frame);
  template<class U>
  void collide(entity<U>);
  std::pair<coord, coord> getBoundingBox();
  void setBoundingBox(std::pair<coord, coord> box);
};

#endif

