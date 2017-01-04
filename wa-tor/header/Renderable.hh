#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

class Renderable{
protected:
  char sym;
public:
  virtual char getSym() = 0;
};

#endif

