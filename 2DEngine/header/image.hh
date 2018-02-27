#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include<vector>
#include<string>
#include<fstream>

template<typename T>
using vec_vec = std::vector<std::vector<T> >;

class image{
private:
  vec_vec<char> mImage;

public:
  image() = default;
  image( const std::string& fileName );
  image( std::fstream&& file );

  void
  readString( const std::string& str );

  void
  readFile( std::fstream&& file );

  vec_vec<char>&
  data();
};

#endif

