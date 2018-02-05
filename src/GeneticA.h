//Autor: Filip Baszak
#pragma once
class GeneticA
{
public:
	int **matrix;
	int verN;
	int finalCost;
	int *finalPath;
	double mutationParameter;
	int populationN;
	int generationN;
	int **population;
	int childNumber;
	int getPathCost(int *path);
	void mutation(int verS, int verE, int *path);
	void printMatrix();
	void printPath(int *path);
	void copyPaths(int *from, int *to);
	int geneticAlgorithm();
	void generateRandPopulation();
	bool allVertices(bool *ver);
	void printPopulation();
	void printNewPopulation(int **newP);
	void reducePopulation(int **pop, int **newPop);
	void reducePopulation2(int **pop, int **newPop);
	int getSpecimen(int **tab, int n);
	int* getBestFromPopulation();
	void crossing(int &counter, int **newP);
	int findInChangeTable(int find, int *table);
	GeneticA();
	GeneticA(int vN, int pN);
	GeneticA(int vN, int pN, int gN, double mN);
	~GeneticA();
};

