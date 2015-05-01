#include<chrono>
#include<cmath>
#include<algorithm>
#include<iostream>
#include"geneticAlgorithm.hh"

std::pair<gene, gene> geneticAlgorithm::breed(gene a, gene b){
  unsigned int cross = generator() % m_geneLength;
  for(unsigned int i = cross; i < m_geneLength; ++i){
    bool swap = a.m_genome[i];
    a.m_genome[i] = b.m_genome[i];
    b.m_genome[i] = swap;
  }
  return std::pair<gene, gene>(a, b);
}

void geneticAlgorithm::init_pop(){
  for(unsigned int i = 0; i < m_popSize; ++i){
    m_genome.push_back(createGene());
  }
}
gene geneticAlgorithm::createGene(){
  gene ret;
  unsigned int threshold = (generator.min() + generator.max()) / 2;

  for(unsigned int j = 0; j < m_geneLength; ++j){
    ret.m_genome[j] = (generator() < threshold);
  }

  return ret;
}

geneticAlgorithm::geneticAlgorithm(){
  typedef std::chrono::high_resolution_clock clock;
  generator.seed(clock::now().time_since_epoch().count());
  init_pop();
}

void geneticAlgorithm::run(){

  for(unsigned int j = 0; j < m_nGenerations; ++j){
    evaluatePop();
    purgePop();
    breedPop();
    mutatePop();
    //displayPop();
  }
}

void geneticAlgorithm::evaluateGene(gene& gene_){
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
  gene_.m_sum = sum;
  gene_.m_prod = prod;

  scaledSumFitness = (sum - m_sumTarget)/m_sumTarget;
  scaledProdFitness = (prod - m_prodTarget)/m_prodTarget;
  scaledFitness = std::abs(scaledSumFitness) + std::abs(scaledProdFitness);

  gene_.m_fitness = scaledFitness;
}

void geneticAlgorithm::evaluatePop(){
  double sumFitness = 0.0;
  for(auto it = m_genome.begin(); it != m_genome.end(); ++it){
    evaluateGene(*it);
    sumFitness += (*it).m_fitness;
  }
  m_avgFitness = sumFitness / m_popSize;
}

void geneticAlgorithm::purgePop(){
  double avg = m_avgFitness;
  m_genome.erase(std::remove_if(m_genome.begin(), m_genome.end(), 
                  [avg](const gene& gene_)->bool{
                    return gene_.m_fitness >= avg;
                  }), m_genome.end());
}

void geneticAlgorithm::breedPop(){
  std::vector<gene> newGenes;
  bool hasFirst = false;
  gene first;
  for(auto it = m_genome.begin(); it != m_genome.end(); ++it){
    if(((double)generator() / generator.max()) < m_recombinationRate){
      if(hasFirst){
        std::pair<gene, gene> tmp(breed(first, *it));
        newGenes.push_back(std::get<0>(tmp));
        newGenes.push_back(std::get<1>(tmp));
        hasFirst = false;
      } else {
        first = *it;
        hasFirst = true;
      }
    }
  }
  for(auto it = newGenes.begin(); it != newGenes.end(); ++it){
    m_genome.push_back(*it);
  }
}

void geneticAlgorithm::mutatePop(){
}

void geneticAlgorithm::displayPop(){
  for(auto it = m_genome.begin(); it != m_genome.end(); ++it){
    for(unsigned int i = 0; i < 10; ++i){
      std::cout << (*it).m_genome[i];
    }
    std::cout << "\t" << (*it).m_fitness << std::endl;
    std::cout << "sum:\t" << (*it).m_sum << " prod:\t" << (*it).m_prod << std::endl;
  }
}

