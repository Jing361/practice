#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

class geneticAlgorithm{
private:
  unsigned int m_popSize = 30;
  unsigned int m_geneLength 10;
  double m_mutationRate = 0.1;
  double m_recombinationRate = 0.5;
  unsigned int m_nGenerations = 100;
  unsigned int m_sumTarget = 36;
  unsigned int m_prodTarget = 360;
  int[30][10] m_gene;
  unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::linear_congruential_engine rand(seed);

  void init_pop();

public:
  geneticAlgorithm();

  void run();
  unsigned int evaluateGene();
};

#endif

