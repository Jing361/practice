#include"physics.hh"

void entity::addEntity(entity& ent){
  m_entity.push_back(ent);
}

void entity::checkCollisions(){
  for(auto it:m_entity){
    for(auto jt:m_entity){
      if(){//TODO:add bounding box collision checking here
        it.collide(jt);
        jt.collide(it);
      }
    }
  }
}

