#ifndef __MARKOV_CHAIN_HH__
#define __MARKOV_CHAIN_HH__

#include<random>
#include<string>
#include<map>
#include<exception>

class invalidInputException : public std::exception {
private:
  std::string mMessage;
  std::string mCulprit;

public:
  invalidInputException( const std::string& param );

  virtual const char* what() const noexcept;
  virtual const char* culprit() const noexcept;
};

class internalErrorException : public std::exception {
private:
  std::string mMessage;

public:
  internalErrorException( );

  virtual const char* what() const noexcept;
};

class word_wrapper{
public:
  unsigned long mCount;
  unsigned long mChance;

  word_wrapper():
    mCount(0),
    mChance(0){
  }
};

//TODO: make template of this class to handle any type, not just strings
class markov_chain{
public:
  const std::string BOUNDARY;
  const unsigned long long CHANCE_TICK;

private:
  std::map<std::string, std::map<std::string, word_wrapper> > mChain;
  std::map<std::string, unsigned long> mWordCounts;
  std::random_device rd;
  mutable std::mt19937 rate;
  mutable std::uniform_int_distribution<> gene;

public:
  markov_chain();

  std::string generate_word( const std::string& lastWord ) const;

  void add( const std::string& word, const std::string& nextWord, double chance = 0.0 );

  void process();

  template<typename OSTREAM>
  OSTREAM& print( OSTREAM& os ){
    for( auto it : mChain ){
      os << it.first << '\t' << mWordCounts[it.first] << '\n';
      for( auto jt : it.second ){
        os << '\t' << jt.first << '\t' << jt.second.mCount << '\t' << jt.second.mChance << '\n';
      }
    }

    return os;
  }
};

#endif

