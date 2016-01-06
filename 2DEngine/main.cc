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
/*    for(auto it:m_buffer){
      for(auto jt:it){
        jt = ' ';
      }
    }*/
    for(unsigned int i = 0; i < X; ++i){
      for(unsigned int j = 0; j < Y; ++j){
        m_buffer[i][j] = ' ';
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

    while(y > 0 && y < Y){
      while(x > 0 && x < X){
        m_buffer[x][y] = img.data()[x][y];
        ++x;
      }
      ++y;
    }
  }
};

int main(){
  buffer<20, 20> frame;
  std::string str("A\n"
                  "BB\n"
                  "CCC\n");
  image img(str);

  frame.render(img, coord(0, 0));
  frame.display();
  return 0;
}

