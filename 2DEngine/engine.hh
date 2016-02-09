#ifndef __ENGINE_HH__
#define __ENGINE_HH__

#include<termios.h>
#include<unistd.h>
#include<thread>
#include<map>
#include<functional>

class bufferedIO{
private:
  bool m_isBuffer = true;

public:
  virtual ~bufferedIO(){
    turnOn();
  }

  void turnOn(){
    struct termios t;
    //get the current terminal I/O structure
    tcgetattr(0, &t);
    //Manipulate the flag bits to do what you want it to do
    t.c_lflag |= ICANON;
    //Apply the new settings
    tcsetattr(0, TCSANOW, &t);
    m_isBuffer = true;
  }

  void turnOff(){
    struct termios t;
    //get the current terminal I/O structure
    tcgetattr(0, &t);
    //Manipulate the flag bits to do what you want it to do
    t.c_lflag &= ~ICANON;
    //Apply the new settings
    tcsetattr(0, TCSANOW, &t);
    m_isBuffer = false;
  }

  void toggleBuffering(){
    if(m_isBuffer){
      turnOff();
    } else {
      turnOn();
    }
  }
};

class engine{
public:
  typedef std::function<void()> callback;

private:
  bool m_end = false;
  std::thread m_wait;
  char m_killChar;
  std::map<char, callback> m_callbacks;

public:
  engine(char kill = 'q');

  virtual ~engine();

  void killThread();
  bool& shouldQuit();
  void registerCallback(char c, callback cb);
};

#endif

