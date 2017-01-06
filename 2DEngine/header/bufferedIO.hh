#ifndef __BUFFEREDIO_HH__
#define __BUFFEREDIO_HH__

#include<termios.h>
#include<unistd.h>
#include<functional>
#include<thread>

class bufferedIO{
private:
  bool mIsBuffer = true;

public:
  virtual ~bufferedIO(){
    turnOn();
  }

  void turnOn(){
    struct termios t;

    //get the current terminal I/O structure
    tcgetattr( 0, &t );

    //Manipulate the flag bits to do what you want it to do
    t.c_lflag |= ICANON;
    //Apply the new settings
    tcsetattr( 0, TCSANOW, &t );

    mIsBuffer = true;
  }

  void turnOff(){
    struct termios t;

    //get the current terminal I/O structure
    tcgetattr( 0, &t );

    //Manipulate the flag bits to do what you want it to do
    t.c_lflag &= ~ICANON;
    //Apply the new settings
    tcsetattr( 0, TCSANOW, &t );

    mIsBuffer = false;
  }

  void toggleBuffering(){
    if( mIsBuffer ){
      turnOff();
    } else {
      turnOn();
    }
  }
};

class IO{
public:
  typedef std::function<void()> callback;

private:
  bool mEnd = false;
  std::thread mWait;
  char mKillChar;
  std::map<char, callback> mCallbacks;

public:
  engine( char kill = 'q' );

  void killThread(){
    char c;
    bufferedIO b;

    b.turnOff();
    while( c != m_killChar && !m_end ){
      c = getchar();
      try{
        m_callbacks.at( c )();
      } catch( std::out_of_range& ){
        //nothing to be done
      }
    }
    m_end = true;
    b.turnOn();
  }
  bool& shouldQuit(){
    return mEnd;
  }
  void registerCallback( char c, callback cb ){
    mCallbacks[c] = cb;
  }
};

#endif

