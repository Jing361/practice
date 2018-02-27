#include<sstream>
#include<utility>

#include"image.hh"

using namespace std;

image::image( const string& fileName )
  : image( fstream( fileName ) ){
}

image::image( fstream&& file ){
  readFile( move( file ) );
}

void
image::readString( const string& str ){
  mImage.clear();

  stringstream ss( str );
  string line;

  while( getline( ss, line ) ){
    mImage.emplace_back( vector<char>( line.begin(), line.end() ) );
  }
}

void
image::readFile( fstream&& file ){
  string str;

  file.seekg( 0, ios::end );
  str.reserve( file.tellg() );
  file.seekg( 0, ios::beg );

  str.assign( ( istreambuf_iterator<char>( file ) ),
                istreambuf_iterator<char>() );
  readString( str );
}

vec_vec<char>&
image::data(){
  return mImage;
}

