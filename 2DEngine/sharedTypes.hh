#ifndef __SHARED_HH__
#define __SHARED_HH__

#include<tuple>

typedef std::pair<int, int> coord;
typedef std::tuple<coord, coord, coord> tri;

coord operator+(const coord& a, const coord& b){
  return coord(a.first + b.first, a.second + b.second);
}

#endif

