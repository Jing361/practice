#ifndef __WORLD_H__
#define __WORLD_H__

template<class T>
class World{
protected:
  T** universe;
  unsigned int height;
  unsigned int width;
public:
  virtual T get(unsigned int x, unsigned int y) = 0;
  virtual void set(unsigned int x, unsigned int y, T newT) = 0;
  virtual T** getPercepts(unsigned int cX, unsigned int cY, unsigned int sX, unsigned int sY) = 0;
};

#endif

