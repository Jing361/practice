#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include<map>
#include<string>
#include<algorithm>

#include"screen.hh"
#include"entity.hh"
#include"image.hh"
#include"shared_types.hh"

template<unsigned int X, unsigned int Y>
class graphics{
private:
  screen<X, Y> mScreen;
  std::map<std::string, image > mImages;
  std::map<std::string, entity<image> > mEntities;

public:
  void drawLine( coord v1, coord v2, char c ){
    int start = std::min( v1.first, v2.first );
    int end = std::max( v1.first, v2.first );
    double slope = ( v2.second - v1.second ) / ( v2.first - v1.first );
    int offset = v1.second - ( slope * v1.first );

    for( ; start <= end; ++start ){
      mScreen.draw( slope * start + offset, start, c );
    }
  }

  void drawFlatLine( int y, int x1, int x2, char c ){
    int start = std::min( x1, x2 );
    int end = std::max( x1, x2 );

    for( ; start <= end; ++start ){
      mScreen.draw( y, start, c );
    }
  }

  void drawFlatTopTri( coord v1, coord v2, coord v3, char c ){
    std::vector<coord> vec{ v1, v2, v3 };
    auto lowIt = std::min_element( vec.begin(), vec.end(), []( coord a, coord b )->bool{
      return a.second < b.second;
    });

    coord low = *lowIt;
    vec.erase( lowIt );
    double liSlope = ( double )( vec[0].first - low.first ) / ( double )( vec[0].second - low.second );
    double riSlope = ( double )( vec[1].first - low.first ) / ( double )( vec[1].second - low.second );
    double xr = low.first;
    double xl = low.first;

    for( unsigned int i = low.second; i < vec[0].second; ++i ){
      drawFlatLine( i, xl, xr, c );
      xl += liSlope;
      xr += riSlope;
    }
  }

  void drawFlatBotTri( coord v1, coord v2, coord v3, char c ){
    std::vector<coord> vec{ v1, v2, v3 };
    auto hiIt = std::max_element( vec.begin(), vec.end(), []( coord a, coord b )->bool{
      return a.second < b.second;
    });

    coord hi = *hiIt;
    vec.erase( hiIt );
    double liSlope = ( double )( vec[0].first - hi.first ) / ( double )( vec[0].second - hi.second );
    double riSlope = ( double )( vec[1].first - hi.first ) / ( double )( vec[1].second - hi.second );
    double xr = hi.first;
    double xl = hi.first;

    for( unsigned int i = hi.second; i > vec[0].second - 1; --i ){
      drawFlatLine( i, xl, xr, c );
      xl -= liSlope;
      xr -= riSlope;
    }
  }

  void drawTri( coord v1, coord v2, coord v3, coord loc, char c ){
    std::vector<coord> vec{ v1, v2, v3 };
    for( coord& it:vec ){
      it.first += loc.first;
      it.second += loc.second;
    }
    std::sort( vec.begin(), vec.end(), [](coord a, coord b ){
      return a.second < b.second;
    });
  
    if( vec[1].second == vec[2].second ){
      drawFlatBotTri( v1, v2, v3, c );
    } else if( vec[0].second == vec[1].second ){
      drawFlatTopTri( v1, v2, v3, c );
    } else {
      coord v4 = coord( ( ( vec[1].second - vec[0].second ) / 
                        ( ( vec[0].second - vec[2].second ) / 
                          ( vec[0].first  - vec[2].first ) ) ) + 
                            vec[0].first, vec[1].second );

      drawFlatTopTri( vec[0], vec[1], v4, c );
      drawFlatBotTri( vec[1], v4, vec[2], c );
    }
  }

  template<typename OSTREAM>
  OSTREAM& tick( OSTREAM& os ){
    mScreen.clear();

    for( auto pr : mEntities ){
      pr.second.draw( *this );
    }
    mScreen.display( os );

    return os;
  }

  void draw( tri t, coord cor ){
    
  }
  void draw( image, coord cor ){
  }
};

#endif

