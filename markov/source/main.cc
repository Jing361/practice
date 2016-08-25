#include<sstream>
#include<fstream>
#include<map>
#include<iostream>
#include<cctype>
#include<string>
#include<locale>

#include<story.hh>

using namespace std;

class word_wrapper{
public:
  unsigned long mCount;
  unsigned long mChance;

  word_wrapper():
    mCount(0),
    mChance(0.0){
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
  unsigned long words = 0;
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
  for(auto wordMap : chain){
    unsigned long count = counts[wordMap.first];
    for(auto word : wordMap.second){
      word.second.mChance = ( double(word.second.mCount) / double(count) ) * 100;
    }
  }

  //output
  for(auto wordMap : chain){
    cout << wordMap.first << '\t' << counts[wordMap.first] << '\n';
    for(auto word : wordMap.second){
      cout << '\t' << word.first << '\t' << word.second.mCount << '\t' << word.second.mChance << '\n';
    }
  }
  cout << flush;

  return 0;
}

