#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include<vector>

#include<graphics.hh>
#include"shared_types.hh"

class basic_pEntity{
private:
  std::vector<basic_pEntity> mParts;
  simple_box mHitBox;
  double mMass;
  vec2 mNetForce;
  vec2 mPosition;
  vec2 mVelocity;
  vec2 mAcceleration;

public:
  basic_pEntity( const basic_pEntity& other )
    : mParts( other.mParts )
    , mHitBox( other.mHitBox )
    , mMass( other.mMass )
    , mNetForce( other.mNetForce )
    , mPosition( other.mPosition )
    , mVelocity( other.mVelocity )
    , mAcceleration( other.mAcceleration ){
  }

  //! @todo use unit datastructure
  basic_pEntity( vec2 pos = {0, 0}, vec2 vel = {0, 0}, vec2 acc = {0, 0},
                 double mass = 1.0, simple_box hit_box = {{0.0, 0.0}, {1.0, 1.0}} )
    : mHitBox( hit_box )
    , mMass( mass )
    , mPosition( pos )
    , mVelocity( vel )
    , mAcceleration( acc ){
  }

  simple_box&
  get_bounding_box(){
    return mHitBox;
  }

  const simple_box&
  get_bounding_box() const{
    return mHitBox;
  }

  vec2&
  get_velocity(){
    return mVelocity;
  }

  vec2&
  get_acceleration(){
    return mAcceleration;
  }

  vec2&
  get_position(){
    return mPosition;
  }

  double&
  get_mass(){
    return mMass;
  }

  double
  get_total_mass() const{
    double total = mMass;

    for( auto part : mParts ){
      total += part.get_total_mass();
    }

    return total;
  }

  void
  tick( double diff ){
    (void) diff;
  }

  void
  apply_force( vec2 force ){
    mNetForce += force;
  }

  vec2
  get_net_force() const{
    return mNetForce;
  }
};

#endif

