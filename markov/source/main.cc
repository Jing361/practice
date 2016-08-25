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

int main( int argc, char** argv ){
  string str;
  if( argc == 2 ){
    str = argv[1];
  } else {
    str = "data/sherlock.txt";
  }

  fstream sher( str );
  story lock( sher );
  map<string, map<string, word_wrapper> > chain;
  map<string, unsigned long> counts;
  string lastWord;

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

        chain[lastWord][word].mCount++;
        ++counts[lastWord];

        lastWord = word;
      }
    }
  }

  //post-process
  for(auto& wordMap : chain){
    unsigned long count = counts[wordMap.first];
    for(auto& word : wordMap.second){
      word.second.mChance = ( ( double(word.second.mCount) / double(count) ) * 100 );
    }
  }

  //output
  std::random_device rd;
  std::mt19937 rate( rd() );
  std::uniform_int_distribution<> dist( 0, chain.size() );
  std::uniform_int_distribution<> gene( 0, 100 );
  unsigned int wordidx = dist( rate ); 
  string lastword;

  for( auto it : chain ){
    wordidx--;
    if( wordidx == 0 ){
      lastword = it.first;
      break;
    }
  }
  cout << lastword << ' ';

  for( unsigned int i = 0; i < 10; ){
    auto ticks = gene( rate );
    auto wordMap = chain[lastword];
    for( auto word : wordMap ){
      ticks -= word.second.mChance;
      if( ticks <= 0 ){
        cout << word.first << ' ';
        lastword = word.first;
        ++i;
        break;
      }
    }
  }

  return 0;
}

