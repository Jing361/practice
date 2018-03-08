#include<cmath>

#include"shared_types.hh"

using namespace std;

bool coordXLess( const coord& a, const coord& b ){
  return get<0>( a ) < get<0>( b );
}

bool coordYLess( const coord& a, const coord& b ){
  return get<1>( a ) < get<1>( b );
}

/*coord operator+( const coord& a, const coord& b ){
  return coord( a.first + b.first, a.second + b.second );
}*/

