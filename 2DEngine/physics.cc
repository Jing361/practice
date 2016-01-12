#include"physics.hh"

template<class T>
void entity::addEntity(entity<T>* ent){
  m_entity.push_back(ent);
}

template<class T>
void entity::checkCollisions(){
  for(auto it:m_entity){
    for(auto jt:m_entity){
      //TODO:add bounding box collision checking
      int d1x = jt.m_coord.second.first  - it.m_coord.first.first;
      int d1y = jt.m_coord.second.second - it.m_coord.first.second;
      int d2x = it.m_coord.second.first  - jt.m_coord.first.first;
      int d2y = it.m_coord.second.second - jt.m_coord.first.second;
      if(!(d1x > 0 || d1y > 0 || d2x > 0 || d2y > 0)){
        it.collide(jt);
        jt.collide(it);
      }
    }
  }
}

