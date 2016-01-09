#include<iostream>
#include<algorithm>
#include<vector>

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawFlatLine(int y, int x1, int x2, char c){
  int start = std::min(x1, x2);
  int end = std::max(x1, x2);
  for(; start <= end; ++start){
    m_buffer[y][start] = c;
  }
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawFlatTopTri(coord v1, coord v2, coord v3, char c){
  std::vector<coord> vec{ v1, v2, v3 };
  auto lowIt = std::min_element(vec.begin(), vec.end(), [](coord a, coord b)->bool{
    return a.second < b.second;
  });

  coord low = *lowIt;
  vec.erase(lowIt);
  double liSlope = (double)(vec[0].first - low.first) / (double)(vec[0].second - low.second);
  double riSlope = (double)(vec[1].first - low.first) / (double)(vec[1].second - low.second);
  double xr = low.first;
  double xl = low.first;

  for(unsigned int i = low.second; i < vec[0].second; ++i){
    drawFlatLine(i, xl, xr, c);
    xl += liSlope;
    xr += riSlope;
  }
}

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawFlatBotTri(coord v1, coord v2, coord v3, char c){
  std::vector<coord> vec{ v1, v2, v3 };
  auto hiIt = std::max_element(vec.begin(), vec.end(), [](coord a, coord b)->bool{
    return a.second < b.second;
  });

  coord hi = *hiIt;
  vec.erase(hiIt);
  double liSlope = (double)(vec[0].first - hi.first) / (double)(vec[0].second - hi.second);
  double riSlope = (double)(vec[1].first - hi.first) / (double)(vec[1].second - hi.second);
  double xr = hi.first;
  double xl = hi.first;

  for(unsigned int i = hi.second; i > vec[0].second; --i){
    drawFlatLine(i, xl, xr, c);
    xl -= liSlope;
    xr -= riSlope;
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
  std::cout << '+';
  for(unsigned int i = 0; i < X; ++i){
    std::cout << '-';
  }
  std::cout << "+\n";

  for(auto it:m_buffer){
    std::cout << '|';
    for(auto jt:it){
      std::cout << jt;
    }
    std::cout << "|\n";
  }

  std::cout << '+';
  for(unsigned int i = 0; i < X; ++i){
    std::cout << '-';
  }
  std::cout << "+\n";

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

template<unsigned int X, unsigned int Y>
void buffer<X, Y>::drawTri(coord v1, coord v2, coord v3, char c){
  std::vector<coord> vec{ v1, v2, v3 };
  std::sort(vec.begin(), vec.end(), [](coord a, coord b){
    return a.second < b.second;
  });
  
  if(vec[1].second == vec[2].second){
    drawFlatBotTri(v1, v2, v3, c);
  } else if(vec[0].second == vec[1].second){
    drawFlatTopTri(v1, v2, v3, c);
  } else {
  coord v4 = coord(((vec[1].second - vec[0].second) / ((vec[0].second - vec[2].second) / (vec[0].first - vec[2].first))) + vec[0].first, vec[1].second);
    
    drawFlatTopTri(vec[0], vec[1], v4, c);
    drawFlatBotTri(vec[1], v4, vec[2], c);
  }
}

