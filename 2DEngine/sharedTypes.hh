#ifndef __SHARED_HH__
#define __SHARED_HH__

#include<tuple>

typedef std::pair<double, double> vec2;
typedef std::pair<int, int> coord;
typedef std::tuple<coord, coord, coord> tri;

coord operator+(const coord& a, const coord& b){
  return coord(a.first + b.first, a.second + b.second);
}

vec2 operator*(const vec2& a, const double& b){
  return vec2(a.first * b, a.second * b);
}

/*vec2 operator*(const vec2& a, const vec2& b){
  return 
}*/

vec2 operator*(const double& a, const vec2& b){
  return b * a;
}

vec2 operator+(const vec2& a, const vec2& b){
  return vec2(a.first + b.first, a.second + b.second);
}

vec2 operator+=(vec2& a, const vec2& b){
  return a = a + b;
}

/*vec2 operator*=(vec2& a, const vec2& b){
  return a = a * b;
}*/

coord operator+(const coord& a, const vec2& b){
  return coord(a.first + (int)b.first, a.second + (int)b.second);
}

#endif

