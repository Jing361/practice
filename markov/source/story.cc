#include<functional> 
#include<cctype>

#include<story.hh>

using namespace std;

string ltrim( string s ) {
  s.erase( s.begin(), find_if( s.begin(), s.end(), not1( ptr_fun<int, int>( ispunct ) ) ) );
  return s;
}

string rtrim( string s ) {
  s.erase( find_if( s.rbegin(), s.rend(), not1( ptr_fun<int, int>( ispunct ) ) ).base(), s.end() );
  return s;
}

string trim( const string& s ) {
  return ltrim( rtrim( s ) );
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

void printRoman( std::string str ){
  std::cout << str << "\t";
  if( story::isRoman( str ) ){
    std::cout << "roman" << std::endl;
  } else {
    std::cout << "not roman" << std::endl;
  }
}

