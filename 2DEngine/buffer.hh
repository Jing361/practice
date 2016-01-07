#ifndef __BUFFER_HH__
#define __BUFFER_HH__

#include<utility>
#include<array>
#include"image.hh"

typedef std::pair<int, int> coord;

template<unsigned int X, unsigned int Y>
class buffer{
private:
  std::array<std::array<char, X>, Y> m_buffer;

public:
  buffer();

  void clear();
  void display();
  void render(image img, coord c);
};

#include"buffer.cc"

#endif

