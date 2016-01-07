#include<iostream>

template<unsigned int X, unsigned int Y>
buffer<X, Y>::buffer(){
  clear();
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::clear(){
  for(auto it = m_buffer.begin(); it < m_buffer.end(); ++it){
    for(auto jt = (*it).begin(); jt < (*it).end(); ++jt){
      *jt = ' ';
    }
  }
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::display(){
  for(auto it:m_buffer){
    for(auto jt:it){
      std::cout << jt;
    }
    std::cout << "\n";
  }
  std::cout << std::flush;
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::render(image img, coord c){
  int x = c.first;
  int y = c.second;
  int i = 0;
  int j = 0;

  while(y >= 0 && y < Y && j < img.data().size()){
    while(x >= 0 && x < X && i < img.data()[j].size()){
      m_buffer[y][x] = img.data()[j][i];
      ++x;
      ++i;
    }
    ++y;
    ++j;
    x = c.first;
    i = 0;
  }
}

