#include<entity.hh>

basic_pEntity::basic_pEntity( const basic_pEntity& other )
  : mParts( other.mParts )
  , mHitBox( other.mHitBox )
  , mMass( other.mMass )
  , mNetForce( other.mNetForce )
  , mPosition( other.mPosition )
  , mVelocity( other.mVelocity )
  , mAcceleration( other.mAcceleration ){
}

basic_pEntity::basic_pEntity( vec2 pos = {0, 0}, vec2 vel = {0, 0}, vec2 acc = {0, 0},
                              double mass = 1.0, simple_box hit_box = {{0.0, 0.0}, {1.0, 1.0}} )
  : mHitBox( hit_box )
  , mMass( mass )
  , mPosition( pos )
  , mVelocity( vel )
  , mAcceleration( acc ){
}

simple_box&
basic_pEntity::get_bounding_box(){
  return mHitBox;
}

const simple_box&
basic_pEntity::get_bounding_box() const{
  return mHitBox;
}

vec2&
basic_pEntity::get_velocity(){
  return mVelocity;
}

vec2&
basic_pEntity::get_acceleration(){
  return mAcceleration;
}

vec2&
basic_pEntity::get_position(){
  return mPosition;
}

double&
basic_pEntity::get_mass(){
  return mMass;
}

double
basic_pEntity::get_total_mass() const{
  double total = mMass;

  for( auto part : mParts ){
    total += part.get_total_mass();
  }

  return total;
}

void
basic_pEntity::tick( double diff ){
  (void) diff;
}

void
basic_pEntity::apply_force( vec2 force ){
  mNetForce += force;
}

vec2
basic_pEntity::get_net_force() const{
  return mNetForce;
}

