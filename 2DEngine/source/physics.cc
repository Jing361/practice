#include<physics.hh>

using namespace std;

void physics::addEntity( const string& name, ent_type ent ){
  mEntities[name] = ent;
}

bool physics::checkCollision( const ent_type& ent1, const ent_type& ent2 ){
  return checkCollision( ent1.getTotalHitBox(), ent2.getTotalHitBox() );
}

bool physics::checkCollision( const string& name1, const string& name2 ){
  return checkCollision( mEntities[name1], mEntities[name2] );
}

void physics::handleCollisions(){
  for(auto pr1 : mEntities ){
    for( auto pr2 : mEntities ){
      if( checkCollision( pr1.second, pr2.second ) ){
        pr1.second.collide( pr2.second );
      }
    }
  }
}

double& physics::damping(){
  return mDamping;
}

void physics::tick( double diff ){
  for( auto pr : mEntities ){
    pr.second.tick( diff );
  }
}

