#include<sstream>
#include<fstream>
#include<iostream>
#include<cctype>
#include<string>
#include<locale>

#include<story.hh>
#include<markov_chain.hh>
#include<argparse.hh>

using namespace std;

int main( int argc, const char** argv ){
  argparse ap;

  ap.add_argument("-data", "data/sherlock.txt", 1);
  ap.add_argument("-words", "10", 1);

  ap.parse_args(argc, argv);

  fstream sher( ap.get_argument<string>( "-data" ) );
  story lock( sher );
  string lastWord;
  markov_chain mc;
  string line;

  // doc parsing
  while( getline( sher, line ) ){
    if( !(lock.isTitle( line ) || trim_space( trim_punct( line ) ) == "" ) ){
      stringstream ss( line );
      string word;
      while( ss >> word ){
        bool endSentence = word[word.size() - 1] == '.';

        if( word == "&" ){
          word = "AND";
        }

        word = trim_punct( word );
        transform( word.begin(), word.end(), word.begin(), [&]( char c ){
          return specialUpper( c );
        } );

        mc.add( lastWord, word );

        lastWord = word;

        if( endSentence ){
          mc.add( lastWord, "." );
          lastWord = "";
        }
      }
    }
  }

  //post-process
  mc.process();

  //output
  lastWord = "";
  for( unsigned int i = 0; i < ap.get_argument<unsigned int>("-words"); ++i){
    lastWord = mc.generate_word( lastWord );
    cout << lastWord << ' ';
  }
  cout << flush;

  return 0;
}

