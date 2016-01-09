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

  void drawFlatLine(int y, int x1, int x2, char c);

public:
  buffer();

  void clear();
  void display();
  void draw(image img, coord c);

  void drawFlatTopTri(coord v1, coord v2, coord v3);
  void drawFlatBotTri(coord v1, coord v2, coord v3);
};

#include"buffer.cc"

#endif

