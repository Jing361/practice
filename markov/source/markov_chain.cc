#include<markov_chain.hh>

using namespace std;

invalidInputException::invalidInputException( const std::string& param ):
  mMessage( "Could not find \"" + param + "\".\n" ),
  mCulprit( param ){
}

const char* invalidInputException::what() const noexcept{
  return mMessage.c_str();
}

const char* invalidInputException::culprit() const noexcept{
  return mCulprit.c_str();
}

markov_chain::markov_chain():
  BOUNDARY(""),
  rd(),
  rate( rd() ),
  gene( 0, 100 ){
}

string markov_chain::generate_word( const string& lastWord ) const{
  if( lastWord == BOUNDARY ){
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
    std::map<std::string, word_wrapper> wordMap;
    try{
      wordMap = mChain.at( lastWord );
    } catch( std::out_of_range& ){
      throw invalidInputException( lastWord );
    }

    for( auto word : wordMap ){
      ticks -= word.second.mChance;
      if( ticks <= 0 ){
        return word.first;
      }
    }
  }

  return BOUNDARY;
}

void markov_chain::add( std::string word, std::string nextWord ){
  ++mChain[word][nextWord].mCount;
  ++mWordCounts[word];
}

void markov_chain::process(){
  for( auto& wordMap : mChain ){
    unsigned long count = mWordCounts[wordMap.first];
    for( auto& word : wordMap.second ){
      word.second.mChance = ( ( double( word.second.mCount ) / double( count ) ) * 100 );
    }
  }
}

