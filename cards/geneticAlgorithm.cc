#include<random>
#include<chrono>
#include"geneticAlgorithm.hh"

void geneticAlgorithm::init_pop(){
  for(unsigned int i = 0; i < m_popSize; ++i){
    for(unsigned int j = 0; j < m_geneLength; ++j){
      m_gene[i][j] = rand();
    }
  }
}

geneticAlgorithm::geneticAlgorithm(){
}

void geneticAlgorithm::run(){
}

unsigned int geneticAlgorithm::evaluateGene(){
}

