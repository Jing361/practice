#include<sstream>
#include<fstream>
#include<map>
#include<iostream>
#include<cctype>
#include<string>
#include<locale>
#include<random>

#include<story.hh>

using namespace std;

class word_wrapper{
public:
  unsigned long mCount;
  unsigned long mChance;

  word_wrapper():
    mCount(0),
    mChance(0){
  }
};

class markov_chain{
private:
  map<string, map<string, word_wrapper> > mChain;
  map<string, unsigned long> mWordCounts;
  random_device rd;
  mt19937 rate;
  uniform_int_distribution<> gene;

public:
  markov_chain():
    rd(),
    rate( rd() ),
    gene( 0, 100 ){
  }

  string generate_word(const string& lastWord){
    if( lastWord == "" ){
      uniform_int_distribution<> dist( 0, mChain.size() );
      unsigned int wordidx = dist( rate );

      for( auto it : mChain ){
        --wordidx;
        if( wordidx == 0 ){
          return it.first;
        }
      }
    } else {
      auto ticks = gene( rate );
      auto wordMap = mChain[lastWord];

      for( auto word : wordMap ){
        ticks -= word.second.mChance;
        if( ticks <= 0 ){
          return word.first;
        }
      }
    }

    return "";
  }
  void add( string word, string nextWord){
    ++mChain[word][nextWord].mCount;
    ++mWordCounts[word];
  }
  void process(){
    for(auto& wordMap : mChain){
      unsigned long count = mWordCounts[wordMap.first];
      for(auto& word : wordMap.second){
        word.second.mChance = ( ( double(word.second.mCount) / double(count) ) * 100 );
      }
    }
  }
};

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

