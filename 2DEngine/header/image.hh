#ifndef __IMAGE_HH__
#define __IMAGE_HH__

#include<vector>
#include<string>

template<typename T>
typedef std::vector<std::vector<T> > dubArr;

class image{
private:
  dubArr<char> mImage;

public:
  image() = default;
  image( const std::string& fileName ){
  }

  void readString( std::string str ){
    std::stringstream ss(str);
    std::string line;
    while( std::getline(ss, line ) ){
      std::vector<char> vec( line.begin(), line.end() );
      m_image.push_back( vec );
    }
  }
  void readFile( std::fstream&& file ){
    std::string str;

    file.seekg( 0, std::ios::end );
    str.reserve( file.tellg() );
    file.seekg( 0, std::ios::beg );

    str.assign( ( std::istreambuf_iterator<char>( file ) ),
                  std::istreambuf_iterator<char>() );
    readString( str );
  }
  dubArr& data(){
    return mImage;
  }
};

#endif

