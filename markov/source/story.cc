#include<functional> 
#include<cctype>

#include<story.hh>

using namespace std;

template<class function>
string& ltrim( string& s, function fn ) {
  s.erase( s.begin(), find_if( s.begin(), s.end(), not1( ptr_fun<int, int>( fn ) ) ) );
  return s;
}

template<class function>
string& rtrim( string& s, function fn ) {
  s.erase( find_if( s.rbegin(), s.rend(), not1( ptr_fun<int, int>( fn ) ) ).base(), s.end() );
  return s;
}

template<class function>
string& trim( string& s, function fn ) {
  return ltrim( rtrim( s, fn ), fn );
}

string ltrim_punct( string s ){
  return ltrim<int(*)(int)>( s, ispunct );
}
string ltrim_space( string s ){
  return ltrim<int(*)(int)>( s, isspace );
}

string rtrim_punct( string s ){
  return rtrim<int(*)(int)>( s, ispunct );
}
string rtrim_space( string s ){
  return rtrim<int(*)(int)>( s, isspace );
}

string trim_punct( string s ){
  return trim<int(*)(int)>( s, ispunct );
}
string trim_space( string s ){
  return trim<int(*)(int)>( s, isspace );
}

char specialUpper( char c ){
  return ( char )::toupper( c );
}

story::story( fstream& file ){
  string str;

  for( unsigned int i = 0; i < 9; ++i ){
    getline( file, str );
  }

  do{
    string ins( str.begin()+6, str.end() );

    transform( ins.begin(), ins.end(), ins.begin(), specialUpper );
    chapters.insert( ins );

    getline( file, str );
  }while( str != "" );
}

bool story::isTitle( string tok ){
  transform( tok.begin(), tok.end(), tok.begin(), specialUpper );
  bool ret = false;

  for_each( chapters.begin(), chapters.end(), [&]( string chapter ){
    string::size_type pos = tok.find( chapter );
    //result is the last thing in the line
    if( pos != string::npos && tok.size() - ( pos + chapter.size() ) == 0 ){
      ret = true;
    }
  } );
  return ret;
}

