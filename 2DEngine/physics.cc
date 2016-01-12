#include"physics.hh"

void entity::addEntity(entity& ent){
  m_entity.push_back(ent);
}

void entity::checkCollisions(){
  for(auto it:m_entity){
    for(auto jt:m_entity){
      //TODO:add bounding box collision checking
      int d1x = jt.second.first  - it.first.first;
      int d1y = jt.second.second - it.first.second;
      int d2x = it.second.first  - jt.first.first;
      int d2y = it.second.second - jt.first.second;
      if(!(d1x > 0 || d1y > 0 || d2x > 0 || d2y > 0)){
        it.collide(jt);
        jt.collide(it);
      }
    }
  }
}

