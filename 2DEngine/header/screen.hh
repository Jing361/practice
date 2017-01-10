#ifndef __SCREEN_HH__
#define __SCREEN_HH__

#include<array>

template<unsigned int X, unsigned int Y>
class screen{
public:
  const static unsigned int WIDTH = X;
  const static unsigned int HEIGHT = X;

private:
  std::array<std::array<char, WIDTH>, HEIGHT> mBuffer;
  char mBorder;
  char mCorner;

public:
  screen( char border = '*' ):
    screen( border, border ){
  }
  screen( char border, char corner ):
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
  template<typename OSTREAM>
  OSTREAM& display( OSTREAM& os ){
    os << mCorner;
    for( unsigned int i = 0; i < WIDTH; ++i ){
      os << mBorder;
    }
    os << mCorner << '\n';

    for( auto arr : mBuffer ){
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

    return os;
  }
  void draw( unsigned int x, unsigned int y, char c ){
    mBuffer[x][y] = c;
  }
};

#endif

