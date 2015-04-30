#include<chrono>
#include<cmath>
#include<algorithm>
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
  std::cout.precision(std::numeric_limits<double>::digits10);
  std::vector<gene> newGenes;
  bool hasFirst = false;
  gene first;

  for(unsigned int j = 0; j < m_nGenerations; ++j){
    double sumFitness = 0.0;
    for(auto it = m_genome.begin(); it != m_genome.end(); ++it){
      double fit = evaluateGene(*it);
      (*it).fitness = fit;
      sumFitness += fit;
    }
    double avg = sumFitness / m_popSize;
    m_genome.erase(std::remove_if(m_genome.begin(), m_genome.end(), 
                    [avg](const gene& gene_)->bool{
                      return gene_.fitness >= avg;
                    }), m_genome.end());
    for(auto it = m_genome.begin(); it != m_genome.end(); ++it){
      if((generator() / generator.max()) < m_recombinationRate){
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

