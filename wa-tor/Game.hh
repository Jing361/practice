#ifndef __GAME_H__
#define __GAME_H__

class Game{
protected:
  bool running;
public:
  virtual void run() = 0;
};

#endif

