#ifndef __SHARED_HH__
#define __SHARED_HH__

#include<tuple>

typedef std::pair<double, double> vec2;
typedef std::pair<unsigned int, unsigned int> coord;
typedef std::tuple<coord, coord, coord> tri;

bool coordXLess( const coord& a, const coord& b );

bool coordYLess( const coord& a, const coord& b );

coord operator+(const coord& a, const coord& b);

vec2 operator*(const vec2& a, const double& b);

vec2 operator/(const vec2& a, const double& b);

/*vec2 operator*(const vec2& a, const vec2& b){
  return 
}*/

vec2 operator*(const double& a, const vec2& b);

vec2 operator+(const vec2& a, const vec2& b);

vec2 operator-(const vec2& a);

vec2 operator+=(vec2& a, const vec2& b);

vec2 normalize(const vec2& x);

/*vec2 operator*=(vec2& a, const vec2& b){
  return a = a * b;
}*/

coord operator+(const coord& a, const vec2& b);

#endif

