#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include<vector>

#include<graphics.hh>
#include<physics.hh>
#include<unit.hh>
#include"shared_types.hh"

class basic_pEntity{
public:
  using mass = gsw::mass<>;
  using time = gsw::time<>;

private:
  std::vector<pEntity> mParts;
  simple_box mHitBox;
  mass mMass;
  vec2_force mNetForce;
  vec2_position mPosition;
  vec2_velocity mVelocity;
  vec2_acceleration mAcceleration;

public:
  basic_pEntity( const basic_pEntity& other );

  //! @todo use unit datastructure
  basic_pEntity( vec2_position pos = {0.0, 0.0}, vec2_velocity vel = {0.0, 0.0}, vec2_acceleration acc = {0.0, 0.0},
                 mass mass = 1.0, simple_box hit_box = {{0.0, 0.0}, {1.0, 1.0}} );

  void
  add_part( pEntity ent ){
    mParts.push_back( ent );
  }

  simple_box&
  get_bounding_box();

  const simple_box&
  get_bounding_box() const;

  vec2_velocity&
  get_velocity();

  vec2_acceleration&
  get_acceleration();

  vec2_position&
  get_position();

  mass&
  get_mass();

  mass
  get_total_mass() const;

  void
  tick( time diff );

  void
  apply_force( vec2_force force );

  vec2_force
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
public:
  using mass = gsw::mass<>;
  using time = gsw::time<>;

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

  vec2_velocity&
  get_velocity();

  vec2_acceleration&
  get_acceleration();

  vec2_position&
  get_position();

  mass&
  get_mass();

  mass
  get_total_mass() const;

  void
  tick( time diff );

  void
  apply_force( vec2_force force );

  vec2_force
  get_net_force() const;

  void
  draw( graphics& gfx ) const;
};

#endif

