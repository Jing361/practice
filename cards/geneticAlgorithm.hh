#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include<random>
#include<vector>
#include<tuple>

class gene{
private:
  //geneLength should be from template value
  //  genes of different length are effectively 
  //  different types as they cannot be bred together
public:
  bool m_genome[10];
  double m_fitness = 0;
  unsigned int m_sum;
  unsigned int m_prod;
};

class geneticAlgorithm{
private:
  unsigned int m_popSize = 30;
  unsigned int m_geneLength = 10;
  unsigned int m_nGenerations = 1000;
  unsigned int m_sumTarget = 36;
  unsigned int m_prodTarget = 360;
  double       m_mutationRate = 0.3;
  double       m_recombinationRate = 0.1;
  double       m_avgFitness;
  std::vector<gene>  m_genome;
  std::minstd_rand generator;

  void init_pop();
  gene createGene();
  std::pair<gene, gene> breed(gene a, gene b);

public:
  geneticAlgorithm();

  void run();
  void evaluateGene(gene& gene_);
  void evaluatePop();
  void purgePop();
  void breedPop();
  void mutatePop();
  void displayPop();
};

#endif

