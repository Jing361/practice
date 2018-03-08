#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<memory>
#include<map>
#include<string>
#include<set>

#include"image.hh"
#include"shared_types.hh"
#include<unit.hh>

class pEntity{
private:
  class interface{
  public:
    virtual
    simple_box&
    get_bounding_box() = 0;

    virtual
    const simple_box&
    get_bounding_box() const = 0;

    virtual
    vec2_velocity&
    get_velocity() = 0;

    virtual
    vec2_acceleration&
    get_acceleration() = 0;

    virtual
    vec2_position&
    get_position() = 0;

    virtual
    gsw::mass<>&
    get_mass() = 0;

    virtual
    gsw::mass<>
    get_total_mass() const = 0;

    virtual
    void
    tick( gsw::time<> ) = 0;

    virtual
    void
    apply_force( vec2_force force ) = 0;

    virtual
    vec2_force
    get_net_force() const = 0;
  };

  template<typename T>
  class wrapper : public interface{
  private:
    T mUnder;

  public:
    wrapper( T t )
      : mUnder( t ){
    }

    simple_box&
    get_bounding_box(){
      return mUnder.get_bounding_box();
    }

    const simple_box&
    get_bounding_box() const{
      return mUnder.get_bounding_box();
    }

    vec2_velocity&
    get_velocity(){
      return mUnder.get_velocity();
    }

    vec2_acceleration&
    get_acceleration(){
      return mUnder.get_acceleration();
    }

    vec2_position&
    get_position(){
      return mUnder.get_position();
    }

    gsw::mass<>&
    get_mass(){
      return mUnder.get_mass();
    }

    gsw::mass<>
    get_total_mass() const{
      return mUnder.get_total_mass();
    }

    void
    tick( gsw::time<> diff ){
      mUnder.tick( diff );
    }

    void
    apply_force( vec2_force force ){
      mUnder.apply_force( force );
    }

    vec2_force
    get_net_force() const{
      return mUnder.get_net_force();
    }
  };

  std::shared_ptr<interface> mIface;

public:
  pEntity() = default;

  pEntity( const pEntity& ) = default;

  pEntity( pEntity&& ) = default;

  template<typename T>
  pEntity( T t )
    : mIface( std::make_shared<wrapper<T> >( t ) ){
  }

  ~pEntity() = default;

  pEntity&
  operator=( const pEntity& ) = default;

  pEntity&
  operator=( pEntity&& ) = default;

  template<typename T>
  pEntity&
  operator=( T t ){
    mIface = std::make_shared<wrapper<T> >( t );

    return *this;
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

  gsw::mass<>&
  get_mass();

  gsw::mass<>
  get_total_mass() const;

  void
  tick( gsw::time<> diff );

  void
  apply_force( vec2_force force );

  vec2_force
  get_net_force() const;
};

class physics{
public:
  using time = gsw::time<>;
  using mass = gsw::mass<>;

private:
  std::map<std::string, pEntity> mEntities;
  double mDamping;

  void
  collide( pEntity& a, pEntity& b );

  void
  do_collisions();

  bool colliding( const pEntity& a, const pEntity& b ) const;

public:
  void
  addEntity( const std::string& name, pEntity ent );

  double&
  damping();

  void
  tick( time diff );
};

class box{
public:
  using time = gsw::time<>;
  using mass = gsw::mass<>;

private:
  simple_box mHitBox;
  mass mMass;
  vec2_force mNetForce;
  vec2_position mPosition;
  vec2_velocity mVelocity;
  vec2_acceleration mAcceleration;

public:
  box( vec2_position position, simple_box hitbox = {{0, 0}, {1, 1}} );

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

#endif

