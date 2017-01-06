#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<map>
#include<string>
#include"shared_types.hh"

class physics{
private:
  std::map<std::string, entity<T> > mEntities;
  double mDamping;

public:
  void addEntity( const std::string& name, entity<T> ent ){
    mEntities[name] = ent;
  }
  bool checkCollision( const hitbox& h1, const hitbox& h2 );
  bool checkCollision( const entity<T>& ent1, const entity<T>& ent2 ){
    return checkCollision( ent1.getTotalHitBox(), ent2.getTotalHitBox() );
  }
  bool checkCollision( const std::string& name1, const std::string& name2 ){
    return checkCollision( mEntities[name1], mEntities[name2] );
  }
  void handleCollisions(){
    for(auto pr1 : mEntities ){
      for( auto pr2 : mEntities ){
        if( checkCollision( pr1.second, pr2.second ) ){
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

