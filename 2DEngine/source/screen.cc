#include<screen.hh>

screen::screen( char border ):
  screen( border, border ){
}

screen::screen( unsigned int X, unsigned int Y, char border, char corner )
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
screen::clear(){
  for( auto& arr : mBuffer ){
    for( auto& c : arr ){
      c = ' ';
    }
  }
}

void
screen::draw( unsigned int x, unsigned int y, char c ){
//the first index indicates the row (which is the y direction), and the second
//  the position in the row(x direction)
  mBuffer[y][x] = c;
}

