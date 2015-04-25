#include<random>
#include<chrono>
#include"geneticAlgorithm.hh"

void geneticAlgorithm::init_pop(){
  unsigned int threshold = (rand.min() + rand.max()) / 2;
  for(unsigned int i = 0; i < m_popSize; ++i){
    for(unsigned int j = 0; j < m_geneLength; ++j){
      if(rand() < threshold){
        m_gene[i][j] = 1;
      } else {
        m_gene[i][j] = 0;
      }
    }
  }
}

geneticAlgorithm::geneticAlgorithm(){
}

void geneticAlgorithm::run(){
}

unsigned int geneticAlgorithm::evaluateGene(){
  return 0;
}

