#include<iostream>
#include<algorithm>
#include<vector>

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawFlatLine(int y, int x1, int x2, char c){
  int start = std::min(x1, x2);
  int end = std::max(x1, x2);
  for(; start < end; ++start){
    m_buffer[y][start] = c;
  }
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawFlatTopTri(coord v1, coord v2, coord v3){
  std::vector<coord> vec{ v1, v2, v3 };
  auto lowIt = std::min_element(vec.begin(), vec.end(), [](coord a, coord b)->bool{
    return a.second < b.second;
  });

  vec.erase(lowIt);
  coord low = *lowIt;
  double liSlope = (vec[0].first - low.first) / (vec[0].second - low.second);
  double riSlope = (vec[1].first - low.first) / (vec[1].second - low.second);
  double xr = low.first;
  double xl = low.first;

  for(unsigned int i = low.second; i < (*lowIt).second; ++i){
    drawFlatLine(i, xl, xr, '#');
    xl = liSlope * i;
    xr = riSlope * i;
  }
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawFlatBotTri(coord v1, coord v2, coord v3){
  std::vector<coord> vec{ v1, v2, v3 };
  auto hiIt = std::max_element(vec.begin(), vec.end(), [](coord a, coord b)->bool{
    return a.second < b.second;
  });

  vec.erase(hiIt);
  coord hi = *hiIt;
  double liSlope = (vec[0].first - hi.first) / (vec[0].second - hi.second);
  double riSlope = (vec[1].first - hi.first) / (vec[1].second - hi.second);
  double xr = hi.first;
  double xl = hi.first;

  for(unsigned int i = hi.second; i > (*hiIt).second; --i){
    drawFlatLine(i, xl, xr, '#');
    xl = liSlope * i;
    xr = riSlope * i;
  }
}

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
void buffer<X, Y>::draw(image img, coord c){
  int x = c.first;
  int y = c.second;
  int i = 0;
  int j = 0;

  while(y >= 0 && y < Y && j < img.data().size()){
    while(x >= 0 && x < X && i < img.data()[j].size()){
      if(img.data()[j][i] != ' '){
        m_buffer[y][x] = img.data()[j][i];
      }
      ++x;
      ++i;
    }
    ++y;
    ++j;
    x = c.first;
    i = 0;
  }
}

