#include<map>
#include<functional>
#include<iostream>
#include<string>
#include<sstream>

#include"engine.hh"
#include"entity.hh"
#include"image.hh"
#include"shared_types.hh"

using namespace std;

int main( int argc, char** argv ){
  if( argc != 2 ){
    return 1;
  }

  engine<80, 40> eng;

  eng.loadConfig( argv[1] );

  eng.run( cout );

  return 0;
}

