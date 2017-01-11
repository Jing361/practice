#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<map>
#include<string>

#include"image.hh"
#include"shared_types.hh"

template<typename ENTITY>
class physics{
public:
  typedef ENTITY ent_type;

private:
  std::map<std::string, ent_type > mEntities;
  double mDamping;

  // collide function only applies physics result to entity a
  void collide( ent_type& a, ent_type& b ){
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
  void addEntity( const std::string& name, ent_type ent ){
    mEntities[name] = ent;
  }

  static bool checkCollision( const typename ent_type::hitbox& h1, const typename ent_type::hitbox& h2 ){
    return false;
  }
  static bool checkCollision( const ent_type& ent1, const ent_type& ent2 ){
    return ent1.isCollide( ent2 );
  }
  bool checkCollision( const std::string& name1, const std::string& name2 ){
    return checkCollision( mEntities[name1], mEntities[name2] );
  }
  void handleCollisions(){
    for(auto pr1 : mEntities ){
      for( auto pr2 : mEntities ){
        if( checkCollision( pr1.second, pr2.second ) ){
          collide( pr1.second, pr2.second );
          pr1.second.collide( pr2.second );
        }
      }
    }
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

