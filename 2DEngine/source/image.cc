#include<sstream>
#include<utility>

#include"image.hh"

using namespace std;

image::image( const string& fileName ):
  image( fstream( fileName ) ){
}

image::image( fstream&& file ){
  readFile( move( file ) );
}

void image::readString( string str ){
  stringstream ss(str);
  string line;
  while( getline(ss, line ) ){
    vector<char> vec( line.begin(), line.end() );
    mImage.push_back( vec );
  }
}

void image::readFile( fstream&& file ){
  string str;

  file.seekg( 0, ios::end );
  str.reserve( file.tellg() );
  file.seekg( 0, ios::beg );

  str.assign( ( istreambuf_iterator<char>( file ) ),
                istreambuf_iterator<char>() );
  readString( str );
}

dubArr<char>& image::data(){
  return mImage;
}

