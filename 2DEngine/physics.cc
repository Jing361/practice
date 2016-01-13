#include"physics.hh"

template<class T>
void physics<T>::addEntity(entity<T>* ent){
  m_entity.push_back(ent);
}

template<class T>
void physics<T>::checkCollisions(){
  //TODO:Prevent redundant collision signals.
  for(auto it:m_entity){
    for(auto jt:m_entity){
      int d1x = jt->getBoundingBox().second.first  - it->getBoundingBox().first.first;
      int d1y = jt->getBoundingBox().second.second - it->getBoundingBox().first.second;
      int d2x = it->getBoundingBox().second.first  - jt->getBoundingBox().first.first;
      int d2y = it->getBoundingBox().second.second - jt->getBoundingBox().first.second;
      if(!(d1x > 0 || d1y > 0 || d2x > 0 || d2y > 0)){
        it->collide(*jt);
        jt->collide(*it);
      }
    }
  }
}

