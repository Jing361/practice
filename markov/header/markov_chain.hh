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
public:
  const std::string BOUNDARY;

private:
  std::map<std::string, std::map<std::string, word_wrapper> > mChain;
  std::map<std::string, unsigned long> mWordCounts;
  std::random_device rd;
  mutable std::mt19937 rate;
  mutable std::uniform_int_distribution<> gene;

public:
  markov_chain();

  std::string generate_word( const std::string& lastWord ) const;

  void add( std::string word, std::string nextWord );

  void process();
};

#endif

