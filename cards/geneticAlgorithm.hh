#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include<random>

class gene{
private:
  unsigned int m_geneLength = 10;
public:
  bool m_genome[10];
  unsigned int fitness;
};

class geneticAlgorithm{
private:
  unsigned int m_popSize = 30;
  unsigned int m_geneLength = 10;
  double       m_mutationRate = 0.1;
  double       m_recombinationRate = 0.5;
  unsigned int m_nGenerations = 100;
  unsigned int m_sumTarget = 36;
  unsigned int m_prodTarget = 360;
  double       m_euthRate = 0.2;
  gene         m_genome[30];
  std::minstd_rand generator;

  void init_pop();
  gene createGene();

public:
  geneticAlgorithm();

  void run();
  unsigned int evaluateGene(gene gene_);
};

#endif

