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

basic_pEntity::basic_pEntity( vec2_position pos, vec2_velocity vel, vec2_acceleration acc,
                              mass mass, simple_box hit_box )
  : mHitBox( hit_box )
  , mMass( mass )
  , mPosition( pos )
  , mVelocity( vel )
  , mAcceleration( acc ){
}

void
basic_pEntity::add_part( pEntity ent ){
  mParts.push_back( ent );
}

simple_box&
basic_pEntity::get_bounding_box(){
  return mHitBox;
}

const simple_box&
basic_pEntity::get_bounding_box() const{
  return mHitBox;
}

vec2_velocity&
basic_pEntity::get_velocity(){
  return mVelocity;
}

vec2_acceleration&
basic_pEntity::get_acceleration(){
  return mAcceleration;
}

vec2_position&
basic_pEntity::get_position(){
  return mPosition;
}

basic_pEntity::mass&
basic_pEntity::get_mass(){
  return mMass;
}

basic_pEntity::mass
basic_pEntity::get_total_mass() const{
  basic_pEntity::mass total = mMass;

  for( auto part : mParts ){
    total += part.get_total_mass();
  }

  return total;
}

void
basic_pEntity::tick( time diff ){
  (void) diff;
}

void
basic_pEntity::apply_force( vec2_force force ){
  mNetForce += force;
}

vec2_force
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
basic_gEntity::draw( graphics& gfx, const vec2_position& pos ) const{
  for( auto part : mParts ){
    part.draw( gfx, pos );
  }

  mEntity.draw( gfx, pos );
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

vec2_velocity&
basic_entity::get_velocity(){
  return mPEntity.get_velocity();
}

vec2_acceleration&
basic_entity::get_acceleration(){
  return mPEntity.get_acceleration();
}

vec2_position&
basic_entity::get_position(){
  return mPEntity.get_position();
}

basic_entity::mass&
basic_entity::get_mass(){
  return mPEntity.get_mass();
}

basic_entity::mass
basic_entity::get_total_mass() const{
  basic_entity::mass total = mPEntity.get_total_mass();

  for( auto part : mParts ){
    total += part.get_total_mass();
  }

  return total;
}

void
basic_entity::tick( time diff ){
  mPEntity.tick( diff );

  for( auto& part : mParts ){
    part.tick( diff );
  }
}

void
basic_entity::apply_force( vec2_force force ){
  mPEntity.apply_force( force );
}

vec2_force
basic_entity::get_net_force() const{
  return mPEntity.get_net_force();
}

void
basic_entity::draw( graphics& gfx, const vec2_position& pos ) const{
  for( auto& part : mParts ){
    part.draw( gfx, pos );
  }

  mGEntity.draw( gfx, pos );
}

