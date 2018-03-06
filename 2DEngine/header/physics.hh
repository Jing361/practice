#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<memory>
#include<map>
#include<string>
#include<set>

#include"image.hh"
#include"shared_types.hh"

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
    vec2&
    get_velocity() = 0;

    virtual
    vec2&
    get_acceleration() = 0;

    virtual
    vec2&
    get_position() = 0;

    virtual
    double&
    get_mass() = 0;

    virtual
    double
    get_total_mass() const = 0;

    virtual
    void
    tick( double ) = 0;

    virtual
    void
    apply_force( vec2 force ) = 0;

    virtual
    vec2
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

    vec2&
    get_velocity(){
      return mUnder.get_velocity();
    }

    vec2&
    get_acceleration(){
      return mUnder.get_acceleration();
    }

    vec2&
    get_position(){
      return mUnder.get_position();
    }

    double&
    get_mass(){
      return mUnder.get_mass();
    }

    double
    get_total_mass() const{
      return mUnder.get_total_mass();
    }

    void
    tick( double diff ){
      mUnder.tick( diff );
    }

    void
    apply_force( vec2 force ){
      mUnder.apply_force( force );
    }

    vec2
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

class physics{
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
  tick( double diff );
};

class box{
private:
  simple_box mHitBox;
  double mMass;
  vec2 mNetForce;
  vec2 mPosition;
  vec2 mVelocity;
  vec2 mAcceleration;

public:
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

#endif

