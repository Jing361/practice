#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<memory>
#include<map>
#include<string>
#include<set>

#include"image.hh"
#include"shared_types.hh"

class entity{
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
    applyForce( vec2 force ) = 0;

    virtual
    vec2
    get_net_force() const = 0;

    virtual
    bool
    operator<( const entity& ) const = 0;
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
    applyForce( vec2 force ){
      mUnder.applyForce( force );
    }

    vec2
    get_net_force() const{
      return mUnder.get_net_force();
    }

    bool
    operator<( const entity& e ) const{
      return mUnder < e;
    }
  };

  std::shared_ptr<interface> mIface;

public:
  entity() = default;

  entity( const entity& ) = default;

  entity( entity&& ) = default;

  template<typename T>
  entity( T t )
    : mIface( std::make_shared<wrapper<T> >( t ) ){
  }

  ~entity() = default;

  entity&
  operator=( const entity& ) = default;

  entity&
  operator=( entity&& ) = default;

  template<typename T>
  entity&
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
  applyForce( vec2 force );

  vec2
  get_net_force() const;

  bool
  operator<( const entity& ) const;
};

class physics{
private:
  std::map<std::string, entity> mEntities;
  double mDamping;

  // collide function only applies physics result to entity a
  void
  collide( entity& a, entity& b );

  std::set<std::set<entity> >
  check_collisions() const;

  bool colliding( const entity& a, const entity& b ) const;

public:
  void
  addEntity( const std::string& name, entity ent );

  double&
  damping();

  void
  tick( double diff );
};

#endif

