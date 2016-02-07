#include<sstream>
#include"image.hh"

image::image(){
}

image::image(std::string str){
  readString(str);
}

image::image(std::fstream&& file){
  readFile(std::move(file));
}

void image::readString(std::string str){
  std::stringstream ss(str);
  std::string line;
  while(std::getline(ss, line, '\n')){
    std::vector<char> vec(line.begin(), line.end());
    m_image.push_back(vec);
  }
}

void image::readFile(std::fstream&& file){
  std::string str;

  file.seekg(0, std::ios::end);
  str.reserve(file.tellg());
  file.seekg(0, std::ios::beg);

  str.assign((std::istreambuf_iterator<char>(file)),
              std::istreambuf_iterator<char>());
  readString(str);
}

std::vector<std::vector<char>>& image::data(){
  return m_image;
}

