#ifndef __STORY_HH__
#define __STORY_HH__

#include<set>
#include<regex>
#include<string>
#include<fstream>
#include<iostream>
#include<algorithm> 

extern std::string ltrim( std::string s );

// trim from end
extern std::string rtrim( std::string s );

// trim from both ends
extern std::string trim( const std::string& s );

char specialUpper( char c );

class story{
public:
  std::set<std::string> chapters;

public:
  story( std::fstream& file );

  bool isTitle( std::string tok );

  static bool isRoman( std::string str ){
    std::regex exp( "[VIXL]+\\." );
    return std::regex_search( str, exp );
  }

};

void printRoman( std::string str );

#endif

