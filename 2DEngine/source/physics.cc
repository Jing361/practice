#include<physics.hh>

using namespace std;

/**********
 * entity *
 **********/

simple_box&
entity::get_bounding_box(){
  return mIface->get_bounding_box();
}

const simple_box&
entity::get_bounding_box() const{
  return mIface->get_bounding_box();
}

vec2&
entity::get_velocity(){
  return mIface->get_velocity();
}

vec2&
entity::get_acceleration(){
  return mIface->get_acceleration();
}

vec2&
entity::get_position(){
  return mIface->get_position();
}

double&
entity::get_mass(){
  return mIface->get_mass();
}

double
entity::get_total_mass() const{
  return mIface->get_total_mass();
}

void
entity::tick( double diff ){
  mIface->tick( diff );
}

void
entity::applyForce( vec2 force ){
  mIface->applyForce( force );
}

bool
entity::operator<( const entity& e ) const{
  return *mIface < e;
}

/***********
 * physics *
 ***********/

set<set<entity> >
physics::check_collisions() const{
  set<set<entity> > ret;

  for( auto ent1 : mEntities ){
    for( auto ent2 : mEntities ){
      if( colliding( ent1.second, ent2.second ) ){
        ret.emplace( set<entity>{ent1.second, ent2.second} );
      }
    }
  }
}

bool physics::colliding( const entity& a, const entity& b ) const{
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

  auto overlap = max( 0, min( aLarge.first,  bLarge.first )
                       - max( aSmall.first,  bSmall.first ) )
               * max( 0, min( aLarge.second, bLarge.second )
                       - max( aSmall.second, bSmall.second ) );

  return overlap > 0;
}

void
physics::collide( entity& a, entity& b ){
  double aMass = a.get_total_mass();
  double bMass = b.get_total_mass();
  auto& aVel = a.get_velocity();
  auto bVel = b.get_velocity();
  auto aMomentum = aMass * aVel;
  auto bMomentum = bMass * bVel;

  aVel = ( ( aMomentum + bMomentum ) * ( bVel - aVel ) ) / ( aMass + bMass );
}

void
physics::addEntity( const string& name, entity ent ){
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
  }

  for( auto coll : check_collisions() ){
    //collide( a, b );
  }
}

