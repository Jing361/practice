//#include<random>
#include<chrono>
#include"geneticAlgorithm.hh"

void geneticAlgorithm::init_pop(){
  typedef std::chrono::high_resolution_clock clock;
  generator.seed(clock::now().time_since_epoch().count());
  unsigned int threshold = (generator.min() + generator.max()) / 2;

  for(unsigned int i = 0; i < m_popSize; ++i){
    for(unsigned int j = 0; j < m_geneLength; ++j){
      m_gene[i][j] = (generator() < threshold);
    }
  }
}

geneticAlgorithm::geneticAlgorithm(){
  init_pop();
}

void geneticAlgorithm::run(){
}

unsigned int geneticAlgorithm::evaluateGene(){
  return 0;
}

