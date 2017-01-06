#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include<map>
#include<string>

#include"screen.hh"
#include"entity.hh"
#include"image.hh"

template<unsigned int X, unsigned int Y>
class graphics{
private:
  screen<X, Y> mScreen;
  std::map<std::string, image > mImages;
  std::map<std::string, entity<T> > mEntities;

public:
  void tick( double diff ){
    mScreen.clear();

    for( auto pr : mEntities ){
      pr.second.draw( mScreen );
    }
    screen.display( ostream );
  }
};

#endif

