#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<memory>
#include<map>
#include<string>

#include"image.hh"
#include"shared_types.hh"

class entity{
private:
  class interface{
  public:
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
  };

  template<typename T>
  class wrapper : public interface{
  private:
    T mUnder;

  public:
    wrapper( T t )
      : mUnder( t ){
    }

    vec2&
    get_velocity(){
      return mUnder.get_velocity()
    }

    vec2&
    get_acceleration(){
      return mUnder.get_acceleration()
    }

    vec2&
    get_position(){
      return mUnder.get_position()
    }

    double&
    get_mass(){
      return mUnder.get_mass()
    }

    double
    get_total_mass() const{
      return mUnder.get_total_mass()
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
  };

  std::shared_ptr<interface> mIface;

public:
  entity() = default;

  entity( const entity& ) = default;

  entity( entity&& ) = default;

  template<typename T>
  entity( T t ){
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

  vec2&
  get_velocity(){
    return mIface->get_velocity()
  }

  vec2&
  get_acceleration(){
    return mIface->get_acceleration()
  }

  vec2&
  get_position(){
    return mIface->get_position()
  }

  double&
  get_mass(){
    return mIface->get_mass()
  }

  double
  get_total_mass() const{
    return mIface->get_total_mass()
  }

  void
  tick( double diff ){
    mIface->tick( diff );
  }

  void
  applyForce( vec2 force ){
    mIface->applyForce( force );
  }

  vec2
  get_net_force() const{
    return mIface->get_net_force();
  }
};

class physics{
private:
  std::map<std::string, entity> mEntities;
  double mDamping;

  // collide function only applies physics result to entity a
  void collide( entity& a, entity& b ){
    double aMass = a.getTotalMass();
    double bMass = b.getTotalMass();
    auto& aVel = a.getVelocity();
    auto bVel = b.getVelocity();

    double pix = ( ( aMass * aVel.first ) + ( bMass * bVel.first ) );
    aVel.first = ( pix + bMass * ( bVel.first - aVel.first ) ) / ( aMass + bMass );

    double piy = ( ( aMass * aVel.second ) + ( bMass * bVel.second ) );
    aVel.second = ( piy + bMass * ( bVel.second - aVel.second ) ) / ( aMass + bMass );
  }

public:
  void addEntity( const std::string& name, entity ent ){
    mEntities[name] = ent;
  }

  double& damping(){
    return mDamping;
  }

  void tick( double diff ){
    for( auto pr : mEntities ){
      pr.second.tick( diff );
    }
  }
};

#endif

