#include<iostream>

#include<graphics.hh>
#include<physics.hh>
#include<entity.hh>

using namespace std;

void
test_graphics(){
  graphics gfx( 15, 15 );


  gfx.add( "tri", tri( {0, 0}, {3, 0}, {0, 3}) );

  gfx.show( cout );


  gfx.draw( tri( {5, 5}, {8, 5}, {5, 8}, '+' ) );

  gfx.show( cout );

  gfx.clearBuffer();


  gfx.draw( tri( {5, 5}, {5, 8}, {8, 5}, '+' ) );

  gfx.show( cout );

  gfx.clearBuffer();


  gfx.draw( tri( {8, 5}, {5, 5}, {5, 8}, '+' ) );

  gfx.show( cout );

  gfx.clearBuffer();


  gfx.draw( tri( {8, 5}, {5, 8}, {5, 5}, '+' ) );

  gfx.show( cout );

  gfx.clearBuffer();


  gfx.draw( tri( {5, 8}, {8, 5}, {5, 5}, '+' ) );

  gfx.show( cout );

  gfx.clearBuffer();


  gfx.draw( tri( {5, 8}, {5, 5}, {8, 5}, '+' ) );

  gfx.show( cout );

  gfx.clearBuffer();


  gfx.show( cout );


  gfx.draw( line( {9, 9}, {0, 7}, '+' ) );

  gfx.show( cout );


  gfx.clearBuffer();


  gfx.draw( line( {0, 7}, {9, 9}, '+' ) );

  gfx.show( cout );


  gfx.clearBuffer();


  gfx.draw( {0, 8}, 'x' );
  gfx.draw( {8, 0}, 'y' );

  gfx.show( cout );
}

void
test_physics(){
  physics psx;

  pEntity e1 = basic_pEntity( {5, 5}, {0, 0}, {0, 0}, 1.0, {{-1, -1}, {1, 1}} );
  pEntity e2 = basic_pEntity();

  psx.addEntity( "A", e1 );
  psx.addEntity( "B", e2 );

  cout << "no move" << endl;
  cout << e1.get_position() << endl;
  cout << e2.get_position() << endl;

  psx.tick( 1 );

  cout << e1.get_position() << endl;
  cout << e2.get_position() << endl;

  cout << "with move" << endl;
  e1.get_velocity() += {1.0, 0.0};

  cout << e1.get_position() << endl;
  cout << e2.get_position() << endl;

  psx.tick( 1 );

  cout << e1.get_position() << endl;
  cout << e2.get_position() << endl;
}

int main(){
//  test_graphics();
  test_physics();

  return 0;
}

