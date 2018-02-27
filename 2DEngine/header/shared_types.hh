#ifndef __SHARED_HH__
#define __SHARED_HH__

#include<tuple>

using vec2 = std::pair<double, double>;
using coord = std::pair<unsigned int, unsigned int>;
using tri = std::tuple<coord, coord, coord>;
using line = std::tuple<coord, coord>;

bool coordXLess( const coord& a, const coord& b );

bool coordYLess( const coord& a, const coord& b );

coord operator+( const coord& a, const coord& b );

vec2 operator*( const vec2& a, const double& b );

vec2 operator/( const vec2& a, const double& b );

/*vec2 operator*(const vec2& a, const vec2& b){
  return 
}*/

vec2 operator*( const double& a, const vec2& b );

vec2 operator+( const vec2& a, const vec2& b );

vec2 operator-( const vec2& a );

vec2 operator+=( vec2& a, const vec2& b );

vec2 normalize( const vec2& x );

/*vec2 operator*=(vec2& a, const vec2& b){
  return a = a * b;
}*/

coord operator+( const coord& a, const vec2& b );

#endif

