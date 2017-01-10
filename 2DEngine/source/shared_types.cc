#include<cmath>

#include"shared_types.hh"

bool coordXLess( const coord& a, const coord& b ){
  return std::get<0>( a ) < std::get<0>( b );
}

bool coordYLess( const coord& a, const coord& b ){
  return std::get<1>( a ) < std::get<1>( b );
}

coord operator+(const coord& a, const coord& b){
  return coord(a.first + b.first, a.second + b.second);
}

vec2 operator*(const vec2& a, const double& b){
  return vec2(a.first * b, a.second * b);
}

vec2 operator/(const vec2& a, const double& b){
  return vec2(a.first / b, a.second / b);
}

vec2 operator*(const double& a, const vec2& b){
  return b * a;
}

vec2 operator+(const vec2& a, const vec2& b){
  return vec2(a.first + b.first, a.second + b.second);
}

vec2 operator-(const vec2& a){
  return vec2(-a.first, -a.second);
}

vec2 operator+=(vec2& a, const vec2& b){
  return a = a + b;
}

vec2 normalize(const vec2& x){
  if(x.first == 0 && x.second == 0){
    return { 0, 0 };
  } else {
    return x / sqrt((x.first * x.first) + (x.second * x.second));
  }
}

coord operator+(const coord& a, const vec2& b){
  return coord(a.first + floor(b.first), a.second + floor(b.second));
}

