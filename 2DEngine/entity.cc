#include"entity.hh"

template<class T>
entity<T>::entity(vec2 pos, vec2 vel, vec2 acc):
  m_pos(pos),
  m_vel(vel),
  m_acc(acc){
}

template<class T>
void entity<T>::addElement(T t, coord cor){
  m_image.push_back(std::pair<T, coord>(t, cor));
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
void entity<T>::collide(entity<U>){
  std::cout << "collision!" << std::endl;
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
void entity<T>::tick(double diff){
  m_pos += m_vel * diff;
  m_vel += m_acc * diff;
}

