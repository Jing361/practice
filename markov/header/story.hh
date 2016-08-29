#ifndef __STORY_HH__
#define __STORY_HH__

#include<set>
#include<regex>
#include<string>
#include<fstream>
#include<iostream>
#include<algorithm> 

extern std::string ltrim_punct( std::string s );
extern std::string ltrim_space( std::string s );

extern std::string rtrim_punct( std::string s );
extern std::string rtrim_space( std::string s );

extern std::string trim_punct( std::string s );
extern std::string trim_space( std::string s );

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

#endif

