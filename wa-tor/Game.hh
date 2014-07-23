#ifndef __GAME_H__
#define __GAME_H__

class Game{
protected:
  bool running;
  unsigned int age;
public:
  virtual void run() = 0;
};

#endif

