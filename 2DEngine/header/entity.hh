#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include<vector>

#include<graphics.hh>
#include<physics.hh>
#include"shared_types.hh"

class basic_pEntity{
private:
  std::vector<pEntity> mParts;
  simple_box mHitBox;
  double mMass;
  vec2 mNetForce;
  vec2 mPosition;
  vec2 mVelocity;
  vec2 mAcceleration;

public:
  basic_pEntity( const basic_pEntity& other );

  //! @todo use unit datastructure
  basic_pEntity( vec2 pos = {0, 0}, vec2 vel = {0, 0}, vec2 acc = {0, 0},
                 double mass = 1.0, simple_box hit_box = {{0.0, 0.0}, {1.0, 1.0}} );

  void
  add_part( pEntity ent ){
    mParts.push_back( ent );
  }

  simple_box&
  get_bounding_box();

  const simple_box&
  get_bounding_box() const;

  vec2&
  get_velocity();

  vec2&
  get_acceleration();

  vec2&
  get_position();

  double&
  get_mass();

  double
  get_total_mass() const;

  void
  tick( double diff );

  void
  apply_force( vec2 force );

  vec2
  get_net_force() const;
};

class basic_gEntity{
private:
  std::vector<gEntity> mParts;
  gEntity mEntity;

public:
  basic_gEntity( gEntity ent );

  basic_gEntity( const basic_gEntity& ) = default;

  basic_gEntity( basic_gEntity&& ) = default;

  basic_gEntity&
  operator=( const basic_gEntity& ) = default;

  basic_gEntity&
  operator=( basic_gEntity&& ) = default;

  void
  add_part( gEntity );

  void
  draw( graphics& gfx ) const;
};

class basic_entity{
private:
  std::vector<basic_entity> mParts;
  pEntity mPEntity;
  gEntity mGEntity;

public:
  basic_entity( pEntity pent, gEntity gent );

  simple_box&
  get_bounding_box();

  const simple_box&
  get_bounding_box() const;

  vec2&
  get_velocity();

  vec2&
  get_acceleration();

  vec2&
  get_position();

  double&
  get_mass();

  double
  get_total_mass() const;

  void
  tick( double diff );

  void
  apply_force( vec2 force );

  vec2
  get_net_force() const;

  void
  draw( graphics& gfx ) const;
};

#endif

