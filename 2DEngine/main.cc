#include<iostream>
#include<string>
#include<sstream>
#include<array>
#include<vector>
#include<utility>

typedef std::pair<int, int> coord;

class image{
private:
  std::vector<std::vector<char>> m_image;

public:
  image(std::string str){
    std::stringstream ss(str);
    std::string line;
    while(std::getline(ss, line, '\n')){
      std::vector<char> vec(line.begin(), line.end());
      m_image.push_back(vec);
    }
  }

  std::vector<std::vector<char>>& data(){
    return m_image;
  }
};

template<unsigned int X, unsigned int Y>
class buffer{
private:
  std::array<std::array<char, X>, Y> m_buffer;

public:
  buffer(){
    clear();
  }

  void clear(){
    for(auto it = m_buffer.begin(); it < m_buffer.end(); ++it){
      for(auto jt = (*it).begin(); jt < (*it).end(); ++jt){
        *jt = ' ';
      }
    }
  }

  void display(){
    for(auto it:m_buffer){
      for(auto jt:it){
        std::cout << jt;
      }
      std::cout << "\n";
    }
    std::cout << std::flush;
  }

  void render(image img, coord c){
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
};

int main(){
  buffer<20, 20> frame;
  std::string str("A\n"
                  "BB\n"
                  "CCC\n");
  image img(str);

  for(unsigned int i = 0; i < 5; ++i){
    frame.clear();
    frame.render(img, coord(10 + i, 10));
    frame.display();
  }
  return 0;
}

