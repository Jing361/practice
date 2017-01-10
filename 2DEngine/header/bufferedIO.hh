#ifndef __BUFFEREDIO_HH__
#define __BUFFEREDIO_HH__

#include<map>
#include<functional>

class bufferedIO{
private:
  bool mIsBuffer = true;

public:
  virtual ~bufferedIO();

  void turnOn();
  void turnOff();

  void toggleBuffering();
};

class IO{
public:
  typedef std::function<void()> callback;

private:
  bool mEnd = false;
  char mKillChar;
  std::map<char, callback> mCallbacks;

public:
  IO( char kill = 'q' );

  void killThread();
  bool& shouldQuit();
  void registerCallback( char c, callback cb );
};

#endif

