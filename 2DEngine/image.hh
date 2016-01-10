#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include<string>
#include<vector>
#include<fstream>

class image{
private:
  std::vector<std::vector<char>> m_image;

  void readString(std::string str);

public:
  image(std::string str);
  image(std::fstream&& file);

  std::vector<std::vector<char>>& data();
};

#endif

