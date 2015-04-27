//#include<random>
#include<chrono>
#include<cmath>
#include<algorithm>
#include"geneticAlgorithm.hh"

bool comp(gene i, gene j){
//return i<j
  return i.fitness < j.fitness;
}

void geneticAlgorithm::init_pop(){
  for(unsigned int i = 0; i < m_popSize; ++i){
    m_genome[i] = createGene();
  }
}
gene geneticAlgorithm::createGene(){
  gene ret;
  typedef std::chrono::high_resolution_clock clock;
  generator.seed(clock::now().time_since_epoch().count());
  unsigned int threshold = (generator.min() + generator.max()) / 2;

  for(unsigned int j = 0; j < m_geneLength; ++j){
    ret.m_genome[j] = (generator() < threshold);
  }

  return ret;
}

geneticAlgorithm::geneticAlgorithm(){
  init_pop();
}

void geneticAlgorithm::run(){
  for(unsigned int j = 0; j < m_nGenerations; ++j){
    for(unsigned int i = 0; i < m_popSize; ++i){
      m_genome[i].fitness = evaluateGene(m_genome[i]);
    }
    std::sort(m_genome, m_genome + m_popSize, comp);
    for(unsigned int i = (1 - m_euthRate) * m_popSize; i < m_popSize; ++i){
      m_genome[i] = createGene();
    }
  }
}

double geneticAlgorithm::evaluateGene(gene gene_){
  int sum  = 0;
  int prod = 1;
  double scaledFitness;
  double scaledSumFitness;
  double scaledProdFitness;

  for(unsigned int i = 0; i < m_geneLength; ++i){
    if(gene_.m_genome[i]){
      sum  += i + 1;
    } else {
      prod *= i + 1;
    }
  }
  scaledSumFitness = (sum - m_sumTarget)/m_sumTarget;
  scaledProdFitness = (prod - m_prodTarget)/m_prodTarget;
  scaledFitness = std::abs(scaledSumFitness) + std::abs(scaledProdFitness);
  return scaledFitness;
}

