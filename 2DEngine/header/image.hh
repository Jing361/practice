#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include<vector>
#include<string>
#include<fstream>

template<typename T>
using dubArr = std::vector<std::vector<T> >;

class image{
private:
  dubArr<char> mImage;

public:
  image() = default;
  image( const std::string& fileName );
  image( std::fstream&& file );

  void readString( std::string str );
  void readFile( std::fstream&& file );
  dubArr<char>& data();
};

#endif

