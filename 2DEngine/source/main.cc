#include<map>
#include<functional>
#include<iostream>
#include<string>
#include<sstream>
#include<exception>

#include"engine.hh"
#include"entity.hh"
#include"image.hh"
#include"shared_types.hh"

using namespace std;

int main( int argc, char** argv ){
  if( argc != 2 ){
    return 1;
  }

  typedef engine<80, 40> eng_type;
  eng_type eng;

  eng.registerConfigCallback("print", []( std::string, std::string w,
                                          resourcemanager<image>&,
                                          std::map<std::string, eng_type::ent_type>&,
                                          std::map<std::string, tri>& ){
    cout << w << endl;
  });

  try{
    eng.loadConfig( argv[1] );
  }catch( exception& e ){
    cout << e.what() << endl;
  }

  eng.run( cout );

  return 0;
}

