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

  fstream lock( ap.get_argument<string>( "-data" ) );
  story sher( lock );
  markov_chain mc;
  const string SENTENCE_BOUNDARY = mc.BOUNDARY;
  string lastWord( SENTENCE_BOUNDARY );
  string line;

  // doc parsing
  while( getline( lock, line ) ){
    if( !(sher.isTitle( line ) || trim_space( trim_punct( line ) ) == "" ) ){
      stringstream ss( line );
      string word;
      while( ss >> word ){
        bool endSentence = ( word.back() == '.' );

        if( word == "&" ){
          word = "AND";
        }

        word = trim_punct( word );
        transform( word.begin(), word.end(), word.begin(), [&]( char c ){
          return specialUpper( c );
        } );

        mc.add( lastWord, word );

        lastWord = word;

        //at the end of a sentence, additionally add the boundary
        if( endSentence ){
          mc.add( lastWord, "." );
          lastWord = SENTENCE_BOUNDARY;
        }
      }
    }
  }

  //post-process
  mc.process();

  //output
  lastWord = SENTENCE_BOUNDARY;
  for( unsigned int i = 0; i < ap.get_argument<unsigned int>("-words"); ++i){
    lastWord = mc.generate_word( lastWord );
    cout << lastWord << ' ';
  }
  cout << flush;

  return 0;
}

