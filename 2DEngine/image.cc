#include<sstream>
#include"image.hh"

image::image(std::string str){
  std::stringstream ss(str);
  std::string line;
  while(std::getline(ss, line, '\n')){
    std::vector<char> vec(line.begin(), line.end());
    m_image.push_back(vec);
  }
}

std::vector<std::vector<char>>& image::data(){
  return m_image;
}

