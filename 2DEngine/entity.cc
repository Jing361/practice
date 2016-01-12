#include"entity.hh"

template<class T>
void entity::addElement(T t, coord cor){
  m_image.push_back(std::pair<T, coord>(t, cor));
}

template<class T>
void entity::draw(buffer& frame){
  for(auto it:m_image){
    frame.draw(it.first, it.second + m_coord);
  }
}

template<class T>
template<class U>
void entity::collide(entity<U>){
  std::cout << "collision!" << std::endl;
}

template<class T>
std::pair<coord, coord> entity::getBoundingBox(){
  return std::pair<coord, coord>(m_box.first + m_coord.first, m_box.second + m_coord.second);
}

void entity::setBoundingBox(std::pair<coord, coord> box){
  m_box = std::pair<coord, coord>
             (coord(std::max(box.first.first, box.second.first),
                    std::max(box.first.second, box.second.second)),
              coord(std::min(box.first.first, box.second.first),
                    std::min(box.first.second, box.second.second)));
}

