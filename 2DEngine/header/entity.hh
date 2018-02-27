#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include<vector>

#include<graphics.hh>
#include"shared_types.hh"

class entity{
public:
  using hitbox = std::pair<coord, coord>;

private:
  std::vector<renderable, coord> mParts;
  hitbox mHitBox;
  double mMass;
  vec2 mNetForce;
  vec2 mPosition;
  vec2 mVelocity;
  vec2 mAcceleration;

public:
  entity( const entity& other )
    : mParts( other.mParts )
    , mHitBox( other.mHitBox )
    , mMass( other.mMass )
    , mNetForce( other.mNetForce )
    , mPosition( other.mPosition )
    , mVelocity( other.mVelocity )
    , mAcceleration( other.mAcceleration ){
  }

  entity( vec2 pos = { 0, 0 }, vec2 vel = { 0, 0 }, vec2 acc = { 0, 0 } )
    : mPosition( pos )
    , mVelocity( vel )
    , mAcceleration( acc ){
  }

  void
  addPart( const renderable& ent, coord cor = coord( 0, 0 ) ){
    mParts.emplace_back( ent, cor );
  }

  template<typename U>
  void
  collide( const entity<U>& ent ){
  }

  const hitbox&
  getHitBox() const{
    return mHitBox;
  }

  hitbox&
  getHitBox(){
    return mHitBox;
  }

  const vec2&
  getPosition() const{
    return mPosition;
  }

  const vec2&
  getVelocity() const{
    return mVelocity;
  }

  const vec2&
  getAcceleration() const{
    return mAcceleration;
  }

  vec2&
  getPosition(){
    return mPosition;
  }

  vec2&
  getVelocity(){
    return mVelocity;
  }

  vec2&
  getAcceleration(){
    return mAcceleration;
  }

  double
  getMass() const{
    return mMass;
  }

  double&
  getMass(){
    return mMass;
  }

  double
  getTotalMass() const{
    double sum = getMass();
    for( auto pt : mParts ){
      sum += std::get<0>( pt ).getTotalMass();
    }
    return sum;
  }

  vec2&
  getNetForce(){
    return mNetForce;
  }

  vec2&
  applyForce( vec2 force );

  void
  tick( double diff ){
    mPosition += diff * mVelocity;
    mVelocity += diff * mAcceleration;
    mAcceleration = mNetForce / getTotalMass();
  }

  template<typename GRAPHICS>
  void
  draw( GRAPHICS& gfx, coord cor = { 0, 0 } ){
    for( auto rndrbl : mParts ){
      gfx.draw( std::get<0>( rndrbl ), std::get<1>( rndrbl ) + mPosition + cor );
    }
  }
};

#endif

