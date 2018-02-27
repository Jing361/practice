#include<iostream>

#include<graphics.hh>

using namespace std;

int main(){
  graphics gfx( 10, 10 );


  gfx.add( "tri", tri( {0, 0}, {3, 0}, {0, 3}) );

  gfx.show( cout );


  gfx.draw( tri( {5,5}, {8,5}, {5,8} ) );

  gfx.show( cout );


  gfx.clearBuffer();

  gfx.show( cout );

  return 0;
}

