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

vec2&
pEntity::get_velocity(){
  return mIface->get_velocity();
}

vec2&
pEntity::get_acceleration(){
  return mIface->get_acceleration();
}

vec2&
pEntity::get_position(){
  return mIface->get_position();
}

double&
pEntity::get_mass(){
  return mIface->get_mass();
}

double
pEntity::get_total_mass() const{
  return mIface->get_total_mass();
}

void
pEntity::tick( double diff ){
  mIface->tick( diff );
}

void
pEntity::apply_force( vec2 force ){
  mIface->apply_force( force );
}

vec2
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

  auto overlap = max( 0.0, min( aLarge.first,  bLarge.first )
                         - max( aSmall.first,  bSmall.first ) )
               * max( 0.0, min( aLarge.second, bLarge.second )
                         - max( aSmall.second, bSmall.second ) );

  return overlap > 0;
}

void
physics::collide( pEntity& a, pEntity& b ){
  double aMass = a.get_total_mass();
  double bMass = b.get_total_mass();
  auto& aVel = a.get_velocity();
  auto& bVel = b.get_velocity();
  auto aMomentum = aMass * aVel;
  auto bMomentum = bMass * bVel;

  aVel = ( ( aMomentum + bMomentum ) * ( bVel - aVel ) ) / ( aMass + bMass );
  bVel = ( ( bMomentum + aMomentum ) * ( aVel - bVel ) ) / ( bMass + aMass );
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
physics::tick( double diff ){
  for( auto ent : mEntities ){
    ent.second.tick( diff );
    auto& vel = ent.second.get_velocity();
    auto& acc = ent.second.get_acceleration();

    ent.second.get_position() += diff * vel;
    vel += diff * acc;
    acc = ent.second.get_net_force() / ent.second.get_total_mass();
  }

  do_collisions();
}

