#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include<string>
#include<vector>
#include<fstream>

class image{
private:
  std::vector<std::vector<char>> m_image;


public:
  image();
  image(std::string str);
  image(std::fstream&& file);

  void readString(std::string str);
  void readFile(std::fstream&& file);
  std::vector<std::vector<char>>& data();
};

#endif

