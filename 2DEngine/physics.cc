#include"physics.hh"

template<class T>
void physics<T>::addEntity(std::string name, entity<T>* ent){
  m_entity.insert(std::pair<std::string, entity<T>*>(name, ent));
}

template<class T>
void physics<T>::checkCollisions(){
  //TODO:Prevent redundant collision signals.
  for(auto it:m_entity){
    for(auto jt:m_entity){
      if(it.first != jt .first){
        int d1x = jt.second->getBoundingBox().second.first - 
                  it.second->getBoundingBox().first.first;
        int d1y = jt.second->getBoundingBox().second.second - 
                  it.second->getBoundingBox().first.second;
        int d2x = it.second->getBoundingBox().second.first  - 
                  jt.second->getBoundingBox().first.first;
        int d2y = it.second->getBoundingBox().second.second - 
                  jt.second->getBoundingBox().first.second;
        if(!(d1x > 0 || d1y > 0 || d2x > 0 || d2y > 0)){
          it.second->collide(*(jt.second));
          jt.second->collide(*(it.second));
        }
      }
    }
  }
}

