#include<markov_chain.hh>

using namespace std;

markov_chain::markov_chain():
  rd(),
  rate( rd() ),
  gene( 0, 100 ){
}

string markov_chain::generate_word( const string& lastWord ){
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

void markov_chain::add( std::string word, std::string nextWord ){
  ++mChain[word][nextWord].mCount;
  ++mWordCounts[word];
}

void markov_chain::process(){
  for(auto& wordMap : mChain){
    unsigned long count = mWordCounts[wordMap.first];
    for(auto& word : wordMap.second){
      word.second.mChance = ( ( double(word.second.mCount) / double(count) ) * 100 );
    }
  }
}
