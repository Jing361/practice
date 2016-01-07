#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include<string>
#include<vector>

class image{
private:
  std::vector<std::vector<char>> m_image;

public:
  image(std::string str);

  std::vector<std::vector<char>>& data();
};

#endif

