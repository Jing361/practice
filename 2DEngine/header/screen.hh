#ifndef __SCREEN_HH__
#define __SCREEN_HH__

#include<vector>

class screen{
public:
  const unsigned int WIDTH;
  const unsigned int HEIGHT;

private:
  std::vector<std::vector<char> > mBuffer;
  char mBorder;
  char mCorner;

public:
  screen( char border = '*' ):
    screen( border, border ){
  }

  screen( unsigned int X, unsigned int Y, char border = '*', char corner = '*' )
    : WIDTH( X )
    , HEIGHT( Y )
    , mBuffer( X )
    , mBorder( border )
    , mCorner( corner ){

    for( auto& line : mBuffer ){
      line.resize( Y );
    }

    clear();
  }

  void
  clear(){
    for( auto& arr : mBuffer ){
      for( auto& c : arr ){
        c = ' ';
      }
    }
  }

  template<typename OSTREAM>
  OSTREAM&
  display( OSTREAM& os ){
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
    for(unsigned int i = 0; i < WIDTH; ++i){
      os << mBorder;
    }
    os << mCorner << '\n';

    return os;
  }

  void
  draw( unsigned int x, unsigned int y, char c ){
    mBuffer[x][y] = c;
  }
};

#endif

