#include<sstream>
#include<fstream>
#include<map>
#include<iostream>
#include<cctype>
#include<string>
#include<locale>

#include<story.hh>

using namespace std;

int main( int argc, char** argv ){
  string str;
  if( argc == 2 ){
    str = argv[1];
  } else {
    str = "data/sherlock.txt";
  }

  fstream sher( str );
  map<string, unsigned int> counts;
  multimap<string, unsigned int> pages;
  story lock( sher );
  unsigned long page = 0;
  unsigned long line = 0;

  // doc parsing
  while( getline( sher, str ) ){
    if( ++line > 40 ){
      ++page;
    }
    if( !lock.isTitle( str ) ){
      stringstream ss( str );
      string word;
      while( ss >> word ){
        word = trim( word );
        transform( word.begin(), word.end(), word.begin(), [&]( char c ){
          return specialUpper( c );
        } );

        pages.insert( make_pair( word, page ) );
        ++counts[word];
      }
    }
  }

  //output
  string lineWord;
  for( auto it = pages.begin(); it != pages.end(); ++it ){
    if( counts[( *it ).first] < 30 ){
      if( lineWord != ( *it ).first ){
        lineWord = ( *it ).first;
        cout << endl << ( *it ).first << '\t';
      }

      cout << ( *it ).second << ", ";
    }
  }

  sher.close();
  return 0;
}

