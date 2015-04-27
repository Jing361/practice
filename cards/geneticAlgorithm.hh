#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include<random>
#include<vector>

class gene{
private:
  unsigned int m_geneLength = 10;
public:
  bool m_genome[10];
  double fitness;
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
  std::vector<gene>  m_genome;
  std::minstd_rand generator;

  void init_pop();
  gene createGene();

public:
  geneticAlgorithm();

  void run();
  double evaluateGene(gene gene_);
};

#endif

