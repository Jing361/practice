#include"entity.hh"

template<class T>
template<class U>
entity<T>::entity(const entity<U>& other):
  entity(other.getPosition(),
         other.getVelocity(),
         other.getAcceleration()){
  m_mass = other.getMass();
  m_box = other.getBoundingBox();
  for(auto it = other.elementBegin(); it != other.elementEnd(); ++it){
    addElement(it.first, it.second);
  }
}

template<class T>
entity<T>::entity(vec2 pos, vec2 vel, vec2 acc):
  m_mass(1.0),
  m_netForce(0, 0),
  m_pos(pos),
  m_vel(vel),
  m_acc(acc){
}

template<class T>
void entity<T>::addElement(T t, coord cor){
  m_image.push_back(std::pair<T, coord>(t, cor));
}

template<class T>
typename std::vector<std::pair<T, coord>>::iterator entity<T>::elementBegin(){
  return m_image.begin();
}

template<class T>
typename std::vector<std::pair<T, coord>>::iterator entity<T>::elementEnd(){
  return m_image.end();
}

template<class T>
void entity<T>::addPart(entity<T> ent, coord cor){
  m_parts.push_back(std::pair<entity<T>, coord>(ent, cor));
}

template<class T>
typename std::vector<std::pair<entity<T>, coord>>::iterator entity<T>::partBegin(){
  return m_parts.begin();
}

template<class T>
typename std::vector<std::pair<entity<T>, coord>>::iterator entity<T>::partEnd(){
  return m_parts.end();
}

template<class T>
template<unsigned int X, unsigned int Y>
void entity<T>::draw(buffer<X, Y>& frame){
  for(auto it:m_image){
    frame.draw(it.first, it.second + m_pos);
  }
}

template<class T>
template<class U>
void entity<T>::collide(entity<U> b){
  double amass = getTotalMass();
  double bmass = b.getTotalMass();

  double pix = ((amass * m_vel.first) + (bmass * b.getVelocity().first));
  m_vel.first = (pix + bmass * (b.getVelocity().first - m_vel.first)) / (amass + bmass);

  double piy = ((amass * m_vel.second) + (bmass * b.getVelocity().second));
  m_vel.second = (piy + bmass * (b.getVelocity().second - m_vel.second)) / (amass + bmass);
}

template<class T>
std::pair<coord, coord> entity<T>::getBoundingBox(){
  return std::pair<coord, coord>(m_box.first + m_pos, m_box.second + m_pos);
}

template<class T>
void entity<T>::setBoundingBox(std::pair<coord, coord> box){
  m_box = std::pair<coord, coord>
             (coord(std::max(box.first.first, box.second.first),
                    std::max(box.first.second, box.second.second)),
              coord(std::min(box.first.first, box.second.first),
                    std::min(box.first.second, box.second.second)));
}

template<class T>
std::pair<coord, coord> entity<T>::getTotalBoundingBox(){
  std::pair<coord, coord> max = getBoundingBox();
  for_each(m_parts.begin(), m_parts.end(), [&](const std::pair<entity<T>, coord>& a){
    auto total = a.first.getTotalBoundingBox();
    max = std::pair<coord, coord>
            (coord(std::max(total.first.first, max.first.first),
                   std::max(total.first.second, max.first.second)),
             coord(std::min(total.second.first, max.second.first),
                   std::min(total.second.second, max.second.second)));
  });
  return max;
}

template<class T>
vec2& entity<T>::getPosition(){
  return m_pos;
}

template<class T>
vec2& entity<T>::getVelocity(){
  return m_vel;
}

template<class T>
vec2& entity<T>::getAcceleration(){
  return m_acc;
}

template<class T>
double& entity<T>::getMass(){
  return m_mass;
}

template<class T>
double entity<T>::getTotalMass(){
  double mass = m_mass;
  for(auto it:m_parts){
    mass += it.first.getMass();
  }
  return mass;
}

template<class T>
vec2& entity<T>::getNetForce(){
  return m_netForce;
}

template<class T>
void entity<T>::applyForce(vec2 f){
  m_netForce += f;
}

template<class T>
void entity<T>::tick(double diff){
  m_pos += m_vel * diff;
  m_vel += m_acc * diff;
  m_acc = m_netForce / m_mass;
}

