#ifndef __PHYSICS_HH__
#define __PHYSICS_HH__

#include<map>
#include<string>

#include"image.hh"
#include"entity.hh"
#include"shared_types.hh"

class physics{
public:
  typedef entity<image> ent_type;

private:
  std::map<std::string, ent_type > mEntities;
  double mDamping;

public:
  void addEntity( const std::string& name, ent_type ent );

  bool checkCollision( const ent_type::hitbox& h1, const ent_type::hitbox& h2 );
  bool checkCollision( const ent_type& ent1, const ent_type& ent2 );
  bool checkCollision( const std::string& name1, const std::string& name2 );
  void handleCollisions();

  double& damping();
  void tick( double diff );
};

#endif

