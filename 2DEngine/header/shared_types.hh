#ifndef __SHARED_HH__
#define __SHARED_HH__

#include<tuple>

using vec2 = std::pair<double, double>;
//using coord = std::pair<int, int>;
using coord = vec2;
using simple_line = std::tuple<coord, coord>;
using simple_box = std::tuple<coord, coord>;
using simple_tri = std::tuple<coord, coord, coord>;

bool coordXLess( const coord& a, const coord& b );

bool coordYLess( const coord& a, const coord& b );

coord operator+( const coord& a, const coord& b );

vec2 operator+( const vec2& a, const vec2& b );

vec2 operator-( const vec2& a, const vec2& b );

vec2 operator-( const vec2& a );

vec2 operator*( const vec2& a, double b );

/*! Technically an invalid vector operation
 */
vec2 operator*( const vec2& a, const vec2& b );

vec2 operator*( double a, const vec2& b );

vec2 operator/( const vec2& a, const double& b );

vec2 operator+=( vec2& a, const vec2& b );

/*! Get unit vector in the same direction
 */
vec2 normalize( const vec2& x );

/*vec2 operator*=(vec2& a, const vec2& b){
  return a = a * b;
}*/

double get_length( const vec2& v );

#endif

