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
  screen( char border = '*' );

  screen( unsigned int X, unsigned int Y, char border = '*', char corner = '*' );

  void
  clear();

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
  draw( unsigned int x, unsigned int y, char c );
};

#endif

