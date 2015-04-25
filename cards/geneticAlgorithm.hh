#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include<random>

class geneticAlgorithm{
private:
  unsigned int m_popSize = 30;
  unsigned int m_geneLength = 10;
  double m_mutationRate = 0.1;
  double m_recombinationRate = 0.5;
  unsigned int m_nGenerations = 100;
  unsigned int m_sumTarget = 36;
  unsigned int m_prodTarget = 360;
  bool m_gene[30][10];
  std::minstd_rand generator;

  void init_pop();

public:
  geneticAlgorithm();

  void run();
  unsigned int evaluateGene();
};

#endif

