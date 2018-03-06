#include<entity.hh>

/*****************
 * basic_pEntity *
 *****************/

basic_pEntity::basic_pEntity( const basic_pEntity& other )
  : mParts( other.mParts )
  , mHitBox( other.mHitBox )
  , mMass( other.mMass )
  , mNetForce( other.mNetForce )
  , mPosition( other.mPosition )
  , mVelocity( other.mVelocity )
  , mAcceleration( other.mAcceleration ){
}

basic_pEntity::basic_pEntity( vec2 pos, vec2 vel, vec2 acc,
                              double mass, simple_box hit_box )
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

/*****************
 * basic_gEntity *
 *****************/

basic_gEntity::basic_gEntity( gEntity ent )
  : mEntity( ent ){
}

void
basic_gEntity::add_part( gEntity ent ){
  mParts.push_back( ent );
}

void
basic_gEntity::draw( graphics& gfx ) const{
  for( auto part : mParts ){
    part.draw( gfx );
  }

  mEntity.draw( gfx );
}

/****************
 * basic_entity *
 ****************/

basic_entity::basic_entity( pEntity pent, gEntity gent )
  : mPEntity( pent )
  , mGEntity( gent ){
}

simple_box&
basic_entity::get_bounding_box(){
  return mPEntity.get_bounding_box();
}

const simple_box&
basic_entity::get_bounding_box() const{
  return mPEntity.get_bounding_box();
}

vec2&
basic_entity::get_velocity(){
  return mPEntity.get_velocity();
}

vec2&
basic_entity::get_acceleration(){
  return mPEntity.get_acceleration();
}

vec2&
basic_entity::get_position(){
  return mPEntity.get_position();
}

double&
basic_entity::get_mass(){
  return mPEntity.get_mass();
}

double
basic_entity::get_total_mass() const{
  double total = mPEntity.get_total_mass();

  for( auto part : mParts ){
    total += part.get_total_mass();
  }

  return total;
}

void
basic_entity::tick( double diff ){
  for( auto& part : mParts ){
    part.tick( diff );
  }
}

void
basic_entity::apply_force( vec2 force ){
  mPEntity.apply_force( force );
}

vec2
basic_entity::get_net_force() const{
  return mPEntity.get_net_force();
}

void
basic_entity::draw( graphics& gfx ) const{
  mGEntity.draw( gfx );
}

