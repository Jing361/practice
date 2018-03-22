#ifndef __SHARED_HH__
#define __SHARED_HH__

#include<tuple>
#include<array>
#include<unit.hh>

template<typename T>
class vec2{
public:
  using value_type = T;

private:
  std::array<T, 2> mData;

public:
  vec2( const std::array<T, 2>& arr )
    : mData( arr ){
  }

  vec2( value_type x = 0.0, value_type y = 0.0 )
    : mData( {x, y} ){
  }

  vec2( const vec2& ) = default;

  vec2( vec2&& ) = default;

  vec2&
  operator=( const vec2& ) = default;

  vec2&
  operator=( vec2&& ) = default;

  T&
  operator[]( size_t idx ){
    return mData[idx];
  }

  const T&
  operator[]( size_t idx ) const{
    return mData[idx];
  }

  size_t
  size() const{
    return mData.size();
  }

  vec2& operator+=( const vec2& b ){
    mData = {mData[0] + b[0], mData[1] + b[1]};

    return *this;
  }

  vec2
  operator+( const vec2& v ) const{
    return {mData[0] + v[0], mData[1] + v[1]};
  }

  vec2
  operator-( const vec2& v ) const{
    return {mData[0] - v[0], mData[1] - v[1]};
  }

  vec2
  operator-() const{
    return {-mData[0], -mData[1]};
  }

/*! Technically an invalid vector operation
 */
  template<typename U>
  vec2<U>
  operator*( const vec2& v ) const{
    return {mData[0] * v[0], mData[1] * v[1]};
  }

  template<typename U, typename W>
  vec2<W>
  operator*( const U& u ){
    return vec2<W>( mData[0] * u, mData[1] * u );
  }

  template<typename U>
  vec2<U>
  operator/( const vec2& b ) const{
    return {mData[0] / b[0], mData[1] / b[1]};
  }

  vec2
  normalize() const{
    if( mData[0] == 0 && mData[1] == 0 ){
      return {0, 0};
    } else {
      return mData / get_length( mData );
    }
  }

  /*! @todo return unit type? */
  double get_length( const vec2& v ){
    return sqrt( ( v[0] * v[0] ) + ( v[1] * v[1] ) );
  }
};

using vec2_velocity     = vec2<gsw::speed<> >;
using vec2_acceleration = vec2<gsw::acceleration<> >;
using vec2_position     = vec2<gsw::length<> >;
using vec2_force        = vec2<gsw::force<> >;

using coord = std::array<double, 2>;
using simple_line = std::tuple<coord, coord>;
using simple_box  = std::tuple<coord, coord>;
using simple_tri  = std::tuple<coord, coord, coord>;

bool coordXLess( const coord& a, const coord& b );

bool coordYLess( const coord& a, const coord& b );

coord operator+( const coord& a, const coord& b );

/*vec2 operator*=(vec2& a, const vec2& b){
  return a = a * b;
}*/

#endif

