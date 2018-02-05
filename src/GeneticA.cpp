//Autor: Filip Baszak
#include "stdafx.h"
#include "GeneticA.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;


GeneticA::GeneticA()
{
	verN = 0;
	populationN = 0;
	generationN = 0;
	finalCost = 0;
	finalPath = NULL;
	matrix = NULL;
	population = NULL;
	matrix = new int*[verN];
	for (int i = 0; i < verN; i++) {
		matrix[i] = new int[verN];
	}
}

GeneticA::GeneticA(int vN, int pN)
{
	verN = vN;
	populationN = pN;
	generationN = 0;
	finalCost = 0;
	finalPath = NULL;
	matrix = NULL;
	population = NULL;
	matrix = new int*[verN];
	for (int i = 0; i < verN; i++) {
		matrix[i] = new int[verN];
	}
	generationN = 10;
	childNumber = pN / 2;
	if (childNumber % 2 != 0) childNumber++;
}

GeneticA::GeneticA(int vN, int pN, int gN, double mN)
{
	verN = vN;
	populationN = pN;
	generationN = 0;
	finalCost = 0;
	finalPath = NULL;
	matrix = NULL;
	population = NULL;
	matrix = new int*[verN];
	for (int i = 0; i < verN; i++) {
		matrix[i] = new int[verN];
	}
	generationN = gN;
	childNumber = pN / 2;
	if (childNumber % 2 != 0) childNumber++;
	mutationParameter = mN;
}

GeneticA::~GeneticA()
{
}

void GeneticA::printMatrix() {
	for (int i = 0; i < verN; i++) {
		for (int j = 0; j < verN; j++) {
			if (matrix[i][j] == -1) {
				cout << matrix[i][j] << " ";
			}
			else {
				if (matrix[i][j] < 10 && matrix[i][j] >= 0) cout << matrix[i][j] << "  ";
				if (matrix[i][j] < 100 && matrix[i][j]>9) cout << matrix[i][j] << " ";
				if (matrix[i][j] < 1000 && matrix[i][j]>99) cout << matrix[i][j];
			}
			cout << " ";
		}
		cout << endl;
	}
}

void GeneticA::printPopulation() {
	for (int i = 0; i < populationN; i++) {
		printPath(population[i]);
		cout << endl;
	}
}

void GeneticA::printNewPopulation(int **newP) {
	for (int i = 0; i < (populationN + childNumber); i++) {
		printPath(newP[i]);
		cout << endl;
	}
}

void GeneticA::printPath(int *path) {
	for (int i = 0; i < verN; i++) {
		if (i == verN - 1) {
			cout << path[i] << " ---> 0" << endl;
		}
		else {
			cout << path[i] << " ---> ";
		}
	}
}

int GeneticA::getPathCost(int *path) {
	int cost = 0;
	for (int i = 0; i < verN - 1; i++) {
		cost += matrix[path[i]][path[i + 1]];
	}
	cost += matrix[path[verN - 1]][0];
	return cost;
}

void GeneticA::copyPaths(int *from, int *to) {
	for (int i = 0; i < verN; i++) {
		to[i] = from[i];
	}
}

void GeneticA::mutation(int verS, int verE, int *path) {
	int temp = 0;;
	temp = path[verS];
	path[verS] = path[verE];
	path[verE] = temp;
}
//stworzenie losowych populacji na pcozatku algorytmu
void GeneticA::generateRandPopulation() {
	population = new int*[populationN];
	bool *visited = new bool[verN];
	int number = 0, counter = 0;
	bool stop = true;
	for (int i = 0; i < populationN; i++) {
		for (int j = 0; j < verN; j++) {
			visited[j] = false;
		}
		population[i] = new int[verN];
		visited[0] = true;
		stop = true;
		counter = 0;
		population[i][counter] = 0;
		counter++;
		while (stop) {
			number = rand() % verN;
			if (visited[number] == false) {
				visited[number] = true;
				population[i][counter] = number;
				counter++;
			}
			if (allVertices(visited)) {
				stop = false;
				//visited[number] = true;
			}
		}
	}
}
//sprawdzenie czy przeszliœmy przez wszystkie wierzcholki
bool GeneticA::allVertices(bool *ver) {
	for (int i = 0; i < verN; i++) {
		if (ver[i] == false) return false;
	}
	return true;
}

void GeneticA::reducePopulation2(int **pop, int **newPop) {
	int **costs = new int*[populationN + childNumber];
	for (int i = 0; i < (populationN + childNumber); i++) {
		costs[i] = new int[2];
		costs[i][0] = getPathCost(newPop[i]);
		costs[i][1] = i;
	}
	for (int i = 0; i < (populationN + childNumber); i++)
	{
		for (int j = 0; j < (populationN + childNumber) - 1; j++)
		{
			if (costs[j][0] > costs[j + 1][0])
				swap(costs[j], costs[j + 1]);
		}
	}
	for (int i = 0; i < (populationN + childNumber); i++) {
		//costs[i][1] = costs[i][1] + costs[i - 1][1];
		//cout << "Osobnik " << i << " ma sciezke o koszcie " << costs[i][0] << endl;
	}
	//mamy tablice z posortowanymi
	for (int i = 0; i < populationN; i++) {
		copyPaths(newPop[costs[i][1]], population[i]);
	}
	for (int i = 0; i < (populationN + childNumber); i++) {
		delete[] costs[i];
	}
	delete[] costs;
}

void GeneticA::reducePopulation(int **pop, int **newPop) {
	int **costs = new int*[populationN + childNumber];
	unsigned int allCost = 0;
	for (int i = 0; i < (populationN + childNumber); i++) {
		costs[i] = new int[2];
		costs[i][0] = getPathCost(newPop[i]);
		allCost += costs[i][0];
		costs[i][1] = i;
	}
	for (int i = 0; i < (populationN + childNumber); i++) {
		costs[i][1] = ((costs[i][0] * 100) / allCost);
	}
	for (int i = 1; i < (populationN + childNumber); i++) {
		costs[i][1] = costs[i][1] + costs[i - 1][1];
		//cout << "Osobnik " << i << " ma sciezke o koszcie " << costs[i][0] << " oraz prawd na punkcie " << costs[i][1] << endl;
	}
	//mamy tablice z kosztami i ich prawdopodobienstwami w %
	unsigned int number;
	int chosen;
	//srand(time(NULL));
	for (int i = 0; i < populationN; i++) {
		
		number = rand() % costs[populationN + childNumber  - 1][1];
		//cout << "Wylosowano: " << number << endl;
		chosen = getSpecimen(costs, number);
		if (chosen == -1) {
			//cout << "\nCoœ siê zepsu³o przy redukowaniu populacji\n";
			_getch();
		}
		if (chosen == -2) {
			//cout << "Wylosowano znowu te sama \. Zmniejszamy i.\n";
			i--;
		}
		//if(chosen >= 0 ) copyPaths(newPop[chosen], population[i]);
		
	}
	for (int i = 0; i < (populationN + childNumber); i++) {
		delete[] costs[i];
	}
	delete[] costs;
}

int GeneticA::getSpecimen(int **tab, int n)
{
	int help = 0;
	for (int i = 0; i < populationN + childNumber; i++) {
		if (i == 0) {
			if (n <= tab[i][1] && tab[i][0] != -1) {
				//cout << "Wybrano do usuniecia osobnika " << i << endl;
				tab[i][0] = -1;
				return 0;
			}
			else {
				if (n <= tab[i][1] && tab[i][0] == -1) {
					return -2;
				}
			}
		}
		else {
			if ((n <= tab[i][1] && n > tab[i-1][1]) && tab[i][0] != -1) {
				//cout << "Wybrano do usuniecia osobnika " << i << endl;
				tab[i][0] = -1;
				return 0;
			}
			else {
				if ((n <= tab[i][1] && n > tab[i - 1][1]) && tab[i][0] == -1) {
					return -2;
				}
			}
		}
	}
	return -1;
}

int GeneticA::findInChangeTable(int find, int *table) {
	for (int i = 0; i < verN; i++) {
		if (table[i] == find) return i;
	}
	return -1;
}

//robienie dzieci
void GeneticA::crossing(int &counter, int **newP) {
	//srand(time(NULL));
	int start = 0, end = 0, firstP = 0, secondP = 0;
	//wylosowanie fragmentu genow rodzicow
	while (start == 0 || start == (verN / 2)) {
		start = rand() % (verN / 2);
	}
	while (end == 0 || end == (verN / 2)) {
		end = rand() % (verN / 2);
	}
	end = end + start;
	//cout << "Kopiujemy genotyp: " << start << " -> " << end << endl;
	//wylosowanie rodzicow
	firstP = rand() % populationN;
	secondP = firstP;
	while (secondP == firstP) {
		secondP = rand() % populationN;
	}
	/*cout << "Rodzic 1:\n";
	printPath(population[firstP]);
	cout << endl;
	cout << "Rodzic 2:\n";
	printPath(population[secondP]);
	cout << endl;*/
	//przekazanie materialu genetycznego
	bool *firstV, *secondV;
	firstV = new bool[verN];
	secondV = new bool[verN];
	int *tableChange = new int[verN];
	for (int i = 0; i < verN;i++) {
		firstV[i] = false;
		secondV[i] = false;
		tableChange[i] = -1;
	}
	firstV[0] = true;
	secondV[0] = true;
	newP[counter][0] = 0;
	newP[counter + 1][0] = 0;
	//w tableChange przechowujemy zmiany sciezki z tych z pierwszego przepisywania - odwzorowania
	//I - przekazanie losowo wylosowanej sciezki
	for (int i = 0; i <= (end-start); i++) {
		newP[counter][start + i] = population[secondP][start + i];
		newP[counter + 1][start + i] = population[firstP][start + i];
		firstV[newP[counter][start + i]] = true;
		secondV[newP[counter + 1][start + i]] = true;
		//zapisanie w tablicy przejsc genetycznych
		tableChange[newP[counter][start + i]] = newP[counter + 1][start + i];
		/*if (tableChange[newP[counter + 1][start + i]] == -1) {
			tableChange[newP[counter + 1][start + i]] = newP[counter][start + i];
		}*/
	}
	/*cout << "Potomek 1 po skopiowaniu gentypu:\n";
	printPath(newP[counter]);
	cout << endl;
	cout << "Potomek 2 po skopiowaniu genotypu:\n";
	printPath(newP[counter + 1]);
	cout << endl;
	cout << "Potomek 1 ma odwiedzone: ";
	for (int j = 0; j < verN; j++) {
		if (firstV[j]) cout << j << ", ";
	}
	cout << endl;
	cout << "Potomek 2 ma odwiedzone: ";
	for (int j = 0; j < verN; j++) {
		if (secondV[j]) cout << j << ", ";
	}
	cout << endl;*/
	//II - uzupelnienie o te co mo¿na uzupe³niæ
	//cos sie pitoli tu ogarnianie ktore wierzcholki byly a ktore nie /
	for (int i = 0; i < verN;i++) {
		if (i < start) {
			if (firstV[population[firstP][i]] == false) {
				newP[counter][i] = population[firstP][i];
				firstV[population[firstP][i]] = true;
			}
			if (secondV[population[secondP][i]] == false) {
				newP[counter + 1][i] = population[secondP][i];
				secondV[population[secondP][i]] = true;
			}
		}
		if (i > end) {
			if (firstV[population[firstP][i]] == false) {
				newP[counter][i] = population[firstP][i];
				firstV[population[firstP][i]] = true;
			}
			if (secondV[population[secondP][i]] == false) {
				newP[counter + 1][i] = population[secondP][i];
				secondV[population[secondP][i]] = true;
			}
		}
	}
	//cout << "Potomek 1 po uzupelnieniu o co mozna:\n";
	//printPath(newP[counter]);
	//cout << endl;
	//cout << "Potomek 2 po uzupelnieniu o co mozna:\n";
	//printPath(newP[counter + 1]);
	//cout << endl;
	//cout << "Potomek 1 ma odwiedzone: ";
	//for (int j = 0; j < verN; j++) {
	//	if (firstV[j]) cout << j << ", ";
	//}
	//cout << endl;
	//cout << "Potomek 2 ma odwiedzone: ";
	//for (int j = 0; j < verN; j++) {
	//	if (secondV[j]) cout << j << ", ";
	//}
	//cout << endl;
	//cout << "Tabela przejsc: \n";
	//for (int i = 0; i < verN; i++) {
	//	cout << i << " <-> " << tableChange[i] << ", ";
	//}
	//cout << endl;
	//III - uzupelnienie reszty o powiazania
	bool stop = true;
	int help = 0;
	for (int i = 0; i < verN; i++) {
		/*if (newP[counter][i] == -1 && newP[counter+1][i] > 0) {
			cout << "Przypadek potomka 1\n";
			help = newP[firstP][i];
			cout << "help wynosi " << help << endl;
			while (stop) {
				
				if (firstV[help] == false) {
					stop = false;
				}
				else {
					help = tableChange[help];
					cout << "help wynosi " << help << endl;
				}
			}
			newP[counter][i] = help;
			firstV[help] = true;
		}
		if (newP[counter][i] > 0 && newP[counter + 1][i] == -1) {
			cout << "Przypadek potomka 2\n";
			
			help = newP[secondP][i];
			cout << "help wynosi " << help << endl;
			help = findInChangeTable(help, tableChange);
			cout << "help wynosi " << help << endl;
			while (stop) {
				//idziemy w druga strone
				if (secondV[help] == false) {
					stop = false;
				}
				else {
					help = findInChangeTable(help, tableChange);
					cout << "help wynosi " << help << endl;
				}
			}
			newP[counter + 1][i] = help;
			secondV[help] = true;
		}*/
		if (newP[counter][i] == -1) {
			//cout << "Przypadek potomka 1\n";
			help = newP[firstP][i];
			//cout << "help wynosi " << help << endl;
			while (stop) {

				if (firstV[help] == false) {
					stop = false;
				}
				else {
					help = tableChange[help];
					//cout << "help wynosi " << help << endl;
				}
			}
			newP[counter][i] = help;
			firstV[help] = true;
		}
		stop = true;
		help = 0;
		if (newP[counter + 1][i] == -1) {
			//cout << "Przypadek potomka 2\n";
			help = newP[secondP][i];
			//cout << "help wynosi " << help << endl;
			//help = findInChangeTable(help, tableChange);
			//cout << "help wynosi " << help << endl;
			while (stop) {
				//idziemy w druga strone
				if (secondV[help] == false) {
					//cout << "W potomku 2 nie odwiedzono " << help << endl;
					stop = false;
				}
				else {
					help = findInChangeTable(help, tableChange);
					//cout << "help wynosi " << help << endl;
				}
			}
			newP[counter + 1][i] = help;
			secondV[help] = true;
		}
		stop = true;
		help = 0;
	}
	
	//cout << "Potomek 1 po calosci:\n";
	//printPath(newP[counter]);
	//cout << endl;
	//cout << "Potomek 2 po calosci:\n";
	//printPath(newP[counter + 1]);
	//cout << endl;
}

int GeneticA::geneticAlgorithm() {
	//srand(time(NULL));
	//int mama = ceil(0.2);
	//cout << "Oto mama:" << mama << endl;
	generateRandPopulation();
	//printPopulation();
	int **newPopulation;
	int counter = 0;
	int mutation = 0, mutation2 = 0, mutationChild = 0, mutationN = ceil(mutationParameter * childNumber);
	int helpM;
	int generations = generationN;
	while (generations > 0) {
		counter = 0;
		
		newPopulation = new int*[populationN + childNumber];
		for (int i = 0; i < (populationN + childNumber); i++) {
			newPopulation[i] = new int[verN];
			if (i < populationN) {
				copyPaths(population[i], newPopulation[i]);
			}
			else {
				for (int j = 0; j < verN; j++) {
					newPopulation[i][j] = -1;
				}
			}
		}
		//cout << "Nowa populacja: \n";
		//printNewPopulation(newPopulation);
		counter = populationN;
		//srand(time(NULL));
		for (int i = 0; i < (childNumber / 2); i++) {
			//uprawianie seksu i robienie dzieci
			crossing(counter, newPopulation);
			counter += 2;
		}
		//losowe mutacje
		//srand(time(NULL));
		for (int i = 0; i < mutationN; i++) {
			mutationChild = rand() % childNumber;
			mutation = 1 + (rand() % (verN - 2));
			mutation2 = mutation;
			while (mutation2 == mutation) {
				mutation2 = 1 + (rand() % (verN - 2));
			}
			helpM = newPopulation[mutationChild + populationN][mutation];
			newPopulation[mutationChild + populationN][mutation] = newPopulation[mutationChild + populationN][mutation2];
			newPopulation[mutationChild + populationN][mutation2] = helpM;
			//cout << "Losowa mutacja w mlodym osobniku numer " << populationN + mutationChild << " na pozycjach "<<mutation<<" oraz "<< mutation2 <<endl;
		}
		//ruletkowa redukcja populacji
		reducePopulation2(population, newPopulation);
		//redukcja licznika
		generations--;
		//usuniecie nowej populacji
		for (int i = 0; i < populationN + childNumber; i++) {
			delete[] newPopulation[i];
		}
		delete newPopulation;
		newPopulation = NULL;
		//printPopulation();
	}
	finalPath = getBestFromPopulation();
	//cout << "Najlepsza sciezka o koszcie: " << finalCost << endl;
	//cout << "Sciezka:\n";
	//printPath(finalPath);
	//finalCost = getPathCost
	return finalCost;
}

int* GeneticA::getBestFromPopulation() {
	int min = MAXINT, minV = 0, help = 0;
	for (int i = 0; i < populationN; i++) {
		help = getPathCost(population[i]);
		if(help < min) {
			min = help;
			minV = i;
		}
	}
	finalCost = min;
	return population[minV];
	
}
