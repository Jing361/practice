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
  hitbox coord> mHitBox;
  double mMass;
  vec2 mNetForce;
  vec2 mPosition;
  vec2 mVelocity;
  vec2 mAcceleration;

public:
  entity( const entity& other );
  entity( vec2 pos = { 0, 0 }, vec2 vel = { 0, 0 }, vec2 acc = { 0, 0 } );

  void addElement( elem_type elem, coord cor = coord( 0, 0 ) );
  void addPart( const entity& ent, coord cor = coord( 0, 0 ) );
  template<typename U>
  void collide( const entity<U>& ent );
  hitbox& getHitBox();
  hitbox getTotalHitBox();
  vec2& getPosition();
  vec2& getVelocity();
  vec2& getAcceleration();
  double& getMass();
  double getTotalMass();
  vec2& getNetForce();
  vec2& applyForce( vec2 force );
  void tick( double diff );
  template<unsigned int X, unsigned int Y>
  void draw( screen<X, Y> scr );
};

#endif

