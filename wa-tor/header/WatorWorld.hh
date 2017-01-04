#ifndef __WATORWORLD_H__
#define __WATORWORLD_H__

#include<map>
#include<vector>
#include<memory>

#include"World.hh"
#include"Entity.hh"

class WatorWorld{
public:
  typedef T value_type;

private:
  std::map<int, std::shared_ptr<Entity> > universe;
  unsigned int height;
  unsigned int width;

public:
  //Specify world size
  //TODO:Implement z-dimension
  WatorWorld(unsigned int x, unsigned int y);
  WatorWorld(unsigned int x, unsigned int y, Entity*** world);
  virtual ~WatorWorld();

  std::shared_ptr<Entity> get( int name );
  std::vector<Entity> getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY);
};

#endif

