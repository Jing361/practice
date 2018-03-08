#include<physics.hh>

using namespace std;

/***********
 * pEntity *
 ***********/

simple_box&
pEntity::get_bounding_box(){
  return mIface->get_bounding_box();
}

const simple_box&
pEntity::get_bounding_box() const{
  return mIface->get_bounding_box();
}

vec2_velocity&
pEntity::get_velocity(){
  return mIface->get_velocity();
}

vec2_acceleration&
pEntity::get_acceleration(){
  return mIface->get_acceleration();
}

vec2_position&
pEntity::get_position(){
  return mIface->get_position();
}

gsw::mass<>&
pEntity::get_mass(){
  return mIface->get_mass();
}

gsw::mass<>
pEntity::get_total_mass() const{
  return mIface->get_total_mass();
}

void
pEntity::tick( gsw::time<> diff ){
  mIface->tick( diff );
}

void
pEntity::apply_force( vec2_force force ){
  mIface->apply_force( force );
}

vec2_force
pEntity::get_net_force() const{
  return mIface->get_net_force();
}

/***********
 * physics *
 ***********/

void
physics::do_collisions(){
  for( auto ent1 : mEntities ){
    for( auto ent2 : mEntities ){
      if( colliding( ent1.second, ent2.second ) ){
        collide( get<1>( ent1 ), get<1>( ent2 ) );
      }
    }
  }
}

bool
physics::colliding( const pEntity& a, const pEntity& b ) const{
  auto aBox = a.get_bounding_box();
  auto bBox = b.get_bounding_box();

  // a small
  auto aSmall = get<0>( aBox );
  // a large
  auto aLarge = get<1>( aBox );

  // b small
  auto bSmall = get<0>( bBox );
  // b large
  auto bLarge = get<1>( bBox );

  auto overlap = max( 0.0, min( aLarge[0],  bLarge[0] )
                         - max( aSmall[0],  bSmall[0] ) )
               * max( 0.0, min( aLarge[1], bLarge[1] )
                         - max( aSmall[1], bSmall[1] ) );

  return overlap > 0;
}

template<typename M, typename V>
static auto
foo( M massA, M massB, V velA, V velB ){
  return ( ( ( 2.0 * massB ) / ( massA + massB ) ) * velB ) - ( ( ( massB - massA ) / ( massA + massB ) ) * velA );
}

void
physics::collide( pEntity& a, pEntity& b ){
  auto aMass = a.get_total_mass();
  auto bMass = b.get_total_mass();
  auto& aVel = a.get_velocity();
  auto& bVel = b.get_velocity();
  auto aVelf = aVel;
  auto bVelf = bVel;
  auto aVelix = aVel[0];
  auto aVeliy = aVel[1];
  auto bVelix = bVel[0];
  auto bVeliy = bVel[1];

  aVelf[0] = foo( aMass, bMass, aVelix, bVelix );
  aVelf[1] = foo( aMass, bMass, aVeliy, bVeliy );
  bVelf[0] = foo( bMass, aMass, bVelix, aVelix );
  bVelf[1] = foo( bMass, aMass, bVeliy, aVeliy );

  aVel = aVelf;
  bVel = bVelf;
}

void
physics::addEntity( const string& name, pEntity ent ){
  mEntities[name] = ent;
}

double&
physics::damping(){
  return mDamping;
}

void
physics::tick( physics::time diff ){
  for( auto& ent : mEntities ){
    ent.second.tick( diff );
    auto& acc = ent.second.get_acceleration();

    for( unsigned int i = 0; i < ent.second.get_position().size(); ++i ){
      auto& vel = ent.second.get_velocity()[i];

      ent.second.get_position()[i] += diff * vel;
      vel += diff * acc[i];

      acc[i] = ent.second.get_net_force()[i] / ent.second.get_total_mass();
    }
  }

  do_collisions();
}

/*******
 * box *
 *******/

box::box( vec2_position position, simple_box hitbox )
  : mHitBox( hitbox )
  , mPosition( position ){
}

simple_box&
box::get_bounding_box(){
  return mHitBox;
}

const simple_box&
box::get_bounding_box() const{
  return mHitBox;
}

vec2_velocity&
box::get_velocity(){
  return mVelocity;
}

vec2_acceleration&
box::get_acceleration(){
  return mAcceleration;
}

vec2_position&
box::get_position(){
  return mPosition;
}

box::mass&
box::get_mass(){
  return mMass;
}

box::mass
box::get_total_mass() const{
  return mMass;
}

void
box::tick( box::time diff ){
  (void) diff;
}

void
box::apply_force( vec2_force force ){
  mNetForce += force;
}

vec2_force
box::get_net_force() const{
  return mNetForce;
}

