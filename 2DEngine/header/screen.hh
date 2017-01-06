#ifndef __SCREEN_HH__
#define __SCREEN_HH__

#include<array>

template<unsigned int X, unsigned int Y>
class screen{
public:
  const static WIDTH = X;
  const static HEIGHT = X;

private:
  std::array<std::array<char, WIDTH>, HEIGHT> mBuffer;
  char mBorder;
  char mCorner;

public:
  screen( char border, char corner = border ):
    mBorder( border ),
    mCorner( corner ){
    clear();
  }

  void clear(){
    for( auto& arr : mBuffer ){
      for( auto& c : arr ){
        c = ' ';
      }
    }
  }
  template<OSTREAM>
  OSTREAM& display( OSTREAM& os ){
    os << mCorner;
    for( unsigned int i = 0; i < WIDTH; ++i ){
      os << mBorder;
    }
    os << mCorner << '\n';

    for( auto arr : m_buffer ){
      os << mBorder;

      for( auto it : arr ){
        os << it;
      }
      os << mBorder << '\n';
    }

    os << mCorner;
    for(unsigned int i = 0; i < X; ++i){
      os << mBorder;
    }
    os << mCorner << '\n';
  }
  void draw( unsigned int X, unsigned int Y, char c ){
    mBuffer[X][Y] = c;
  }
};

#endif

