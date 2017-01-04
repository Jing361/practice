#ifndef __GAME_H__
#define __GAME_H__

class Game{
protected:
  bool running;
  unsigned int age;
public:
  Game():
    running( false ),
    age( 0 ){  }
  virtual void run() = 0;
};

#endif

