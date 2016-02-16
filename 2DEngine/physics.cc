#include<set>
#include"physics.hh"

template<class T>
bool physics<T>::checkCollision(const std::pair<coord, coord>& box1, const std::pair<coord, coord>& box2){
/*  int d1x = box1.second.first  - box1.first.first  - box2.first.first;
  int d2x = box1.second.first  - box1.first.first  - box2.second.first;
  int d1y = box1.second.second - box1.first.second - box2.first.second;
  int d2y = box1.second.second - box1.first.second - box2.second.second;
std::cout << d1x << '\t' << d2x << '\t' << d1y << '\t' << d2y << std::endl;
*/
  if((((box1.second.first < box2.first.first) && 
       (box2.first.first < box1.first.first)) ||
      ((box1.second.first < box2.second.first) && 
       (box2.second.first < box1.first.first))) &&
     (((box1.second.second < box2.first.second) && 
       (box2.first.second < box1.first.second)) ||
      ((box1.second.second < box2.second.second) && 
       (box2.second.second < box1.first.second)))){
    return true;
  } else {
    return false;
  }

 /* if((d1x < 0 || d2x < 0) && (d1y < 0 || d2y < 0)){
    return true;
  } else {
    return false;
  }*/
}

template<class T>
void physics<T>::addEntity(std::string name, entity<T>* ent){
  m_entity.insert(std::pair<std::string, entity<T>*>(name, ent));
}

template<class T>
void physics<T>::checkCollisions(){
  typedef std::pair<std::string, std::string> names;
  std::set<names> colls;
  //TODO:Prevent redundant collision signals.
  for(auto it:m_entity){
    for(auto jt:m_entity){
      if(it.first != jt .first){
        auto iBox = it.second->getBoundingBox();
        auto jBox = jt.second->getBoundingBox();
/*        int d1x = jBox.second.first - 
                  iBox.first.first;
        int d1y = jBox.second.second - 
                  iBox.first.second;
        int d2x = iBox.second.first  - 
                  jBox.first.first;
        int d2y = iBox.second.second - 
                  jBox.first.second;
        */
        if(checkCollision(iBox, jBox)){
        //if(!(d1x > 0 || d1y > 0 || d2x > 0 || d2y > 0)){
          if(!colls.count(names(it.first, jt.first))){
            entity<T> tmp(*it.second);
            it.second->collide(*(jt.second));
            jt.second->collide(tmp);
            colls.insert(names(jt.first, it.first));
          }
        }
      }
    }
  }
}

template<class T>
void physics<T>::setDamping(double f){
  m_dampingForce = f;
}

template<class T>
void physics<T>::tick(double diff){
  for(auto it:m_entity){
    auto ent = it.second;
    ent->applyForce(m_dampingForce * -ent->getVelocity());
    ent->tick(diff / (CLOCKS_PER_SEC * 10));
    ent->getNetForce() = { 0, 0 };
    ent->getAcceleration() = { 0, 0 };
  }
}

