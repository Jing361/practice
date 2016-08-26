#include<sstream>
#include<fstream>
#include<iostream>
#include<cctype>
#include<string>
#include<locale>

#include<story.hh>
#include<markov_chain.hh>

using namespace std;

int main( int argc, char** argv ){
  string str;
  if( argc == 2 ){
    str = argv[1];
  } else {
    str = "data/sherlock.txt";
  }

  fstream sher( str );
  story lock( sher );
  string lastWord;
  markov_chain mc;

  // doc parsing
  while( getline( sher, str ) ){
    if( !lock.isTitle( str ) ){
      stringstream ss( str );
      string word;
      while( ss >> word ){
        word = trim( word );
        transform( word.begin(), word.end(), word.begin(), [&]( char c ){
          return specialUpper( c );
        } );

        mc.add(lastWord, word);

        lastWord = word;
      }
    }
  }

  //post-process
  mc.process();

  //output
  lastWord = mc.generate_word( "" );
  for( unsigned int i = 0; i < 10; ++i){
    cout << lastWord << ' ';
    lastWord = mc.generate_word( lastWord );
  }

  return 0;
}

