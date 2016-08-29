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
  unsigned int wordCount;
  if( argc >= 1 ){
    str = argv[1];
  } else {
    str = "data/sherlock.txt";
  }
  if( argc == 3){
    wordCount = std::atoi( argv[2] );
  } else {
    wordCount = 10;
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
  for( unsigned int i = 0; i < wordCount; ++i){
    cout << lastWord << ' ';
    lastWord = mc.generate_word( lastWord );
  }

  return 0;
}

