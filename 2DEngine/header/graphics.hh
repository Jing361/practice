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
  std::map<std::string, entity<image> > mEntities;

public:
  template<typename OSTREAM>
  OSTREAM& tick( double diff, OSTREAM& os ){
    mScreen.clear();

    for( auto pr : mEntities ){
      pr.second.draw( mScreen );
    }
    mScreen.display( os );

    return os;
  }
};

#endif

