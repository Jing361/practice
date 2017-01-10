#include<termios.h>
#include<unistd.h>

#include"bufferedIO.hh"

using namespace std;

bufferedIO::~bufferedIO(){
  turnOn();
}

void bufferedIO::turnOn(){
  struct termios t;

  //get the current terminal I/O structure
  tcgetattr( 0, &t );

  //Manipulate the flag bits to do what you want it to do
  t.c_lflag |= ICANON;
  //Apply the new settings
  tcsetattr( 0, TCSANOW, &t );

  mIsBuffer = true;
}

void bufferedIO::turnOff(){
  struct termios t;

  //get the current terminal I/O structure
  tcgetattr( 0, &t );

  //Manipulate the flag bits to do what you want it to do
  t.c_lflag &= ~ICANON;
  //Apply the new settings
  tcsetattr( 0, TCSANOW, &t );

  mIsBuffer = false;
}

void bufferedIO::toggleBuffering(){
  if( mIsBuffer ){
    turnOff();
  } else {
    turnOn();
  }
}



IO::IO( char kill ):
  mKillChar( kill ){
}

void IO::killThread(){
  char c = ~mKillChar;
  bufferedIO b;

  b.turnOff();
  while( c != mKillChar && !mEnd ){
    c = getchar();
    try{
      mCallbacks.at( c )();
    } catch( out_of_range& ){
      //nothing to be done
    }
  }
  mEnd = true;
  b.turnOn();
}

bool& IO::shouldQuit(){
  return mEnd;
}

void IO::registerCallback( char c, callback cb ){
  mCallbacks[c] = cb;
}

