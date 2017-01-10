#ifndef __ENTITY_HH__
#define __ENTITY_HH__

#include<vector>

#include"screen.hh"
#include"shared_types.hh"

template<typename IMAGE>
class entity{
public:
  typedef IMAGE elem_type;
  typedef std::pair<coord, coord> hitbox;

private:
  std::vector<std::pair<elem_type, coord> > mElements;
  std::vector<std::pair<entity<elem_type>, coord> > mParts;
  hitbox mHitBox;
  double mMass;
  vec2 mNetForce;
  vec2 mPosition;
  vec2 mVelocity;
  vec2 mAcceleration;

public:
  entity( const entity& other ):
    mElements( other.mElements ),
    mParts( other.mParts ),
    mHitBox( other.mHitBox ),
    mMass( other.mMass ),
    mNetForce( other.mNetForce ),
    mPosition( other.mPosition ),
    mVelocity( other.mVelocity ),
    mAcceleration( other.mAcceleration ){
  }
  entity( vec2 pos = { 0, 0 }, vec2 vel = { 0, 0 }, vec2 acc = { 0, 0 } ){
  }

  void addElement( elem_type elem, coord cor = coord( 0, 0 ) ){
    mElements.emplace_back( elem, cor );
  }
  void addPart( const entity& ent, coord cor = coord( 0, 0 ) ){
    mParts.emplace_back( ent, cor );
  }

  template<typename U>
  void collide( const entity<U>& ent );
  const hitbox& getHitBox() const{
    return mHitBox;
  }
  hitbox& getHitBox(){
    return mHitBox;
  }
  hitbox getTotalHitBox() const;

  const vec2& getPosition() const{
    return mPosition;
  }
  const vec2& getVelocity() const{
    return mVelocity;
  }
  const vec2& getAcceleration() const{
    return mAcceleration;
  }

  vec2& getPosition(){
    return mPosition;
  }
  vec2& getVelocity(){
    return mVelocity;
  }
  vec2& getAcceleration(){
    return mAcceleration;
  }
  double& getMass(){
    return mMass;
  }
  double getTotalMass() const{
    double sum = getMass();
    for( auto pt : mParts ){
      sum += pt.getTotalMass();
    }
    return sum;
  }
  vec2& getNetForce();
  vec2& applyForce( vec2 force );

  void tick( double diff );
  template<unsigned int X, unsigned int Y>
  void draw( screen<X, Y> scr );
};

#endif

