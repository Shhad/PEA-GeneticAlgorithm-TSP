// pea_3.cpp : Defines the entry point for the console application.
//Autor: Filip Baszak

#include "stdafx.h"
#include "Parser.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <Windows.h>

using namespace std;

int getAverage(int *table) {
	int average = 0;
	for (int i = 0; i < 10; i++) {
		average = average + table[i];
	}
	return (average / 10);
}

int getAverage(long *table) {
	int average = 0;
	for (int i = 0; i < 10; i++) {
		average = average + table[i];
	}
	return (average / 10);
}
int main()
{
	srand(time(NULL));
	int choice = 0;
	int path = 0;
	double times = 0;
	clock_t start;
	clock_t end;
	cout << "1 - program, 2 - testy";
	cin >> choice;
	if (choice == 1) {
		//srand(time(NULL));
		Parser *p = new Parser();
		start = clock();
		path = p->problem->geneticAlgorithm();
		end = clock();
		cout << "Algorytm genetyczny wytypowal sciezke o wartosci: " << path << endl;
		cout << "Sciezka:" << endl;
		p->problem->printPath(p->problem->finalPath);
		cout << endl << "Czas: " << (end - start)<<endl;
	}
	if (choice == 2) {
		int populationNumber = 1000;
		int generationsNumber = 1000;
		double mutation = 0.1;
		string file;
		cout << endl << "WYNIKI DLA: \nLICZBA POPULACJI - " << populationNumber << "\nLICZBA POKOLEN - " << generationsNumber << "\nMUTACJE - " << mutation << endl << endl;
		//---------------------------------------------
		file = "gr17.tsp";
		cout << "Dla pliku " << file << endl;
		Parser *p = new Parser(file, populationNumber, generationsNumber, mutation);
		times = 0;
		int *table = new int[10];
		long *timeTable = new long[10];
		path = 0;
		//srand(time(NULL));
		start;
		end;
		for (int i = 0; i < 10; i++) {
			start = clock();
			p->problem->geneticAlgorithm();
			end = clock();
			table[i] = p->problem->finalCost;
			timeTable[i] = ((long)end - (long)start);
		}
		times = getAverage(timeTable);
		path = getAverage(table);
		cout << "Sredni koszt: " << path << endl;
		cout << "Średni czas: " << times << endl << endl;
		delete p;
		p = NULL;
		//---------------------------------------
		Sleep(500);
		file = "gr21.tsp";
		cout << "Dla pliku " << file << endl;
		p = new Parser(file, populationNumber, generationsNumber, mutation);

		//srand(time(NULL));

		for (int i = 0; i < 10; i++) {
			start = clock();
			p->problem->geneticAlgorithm();
			end = clock();
			table[i] = p->problem->finalCost;
			timeTable[i] = ((long)end - (long)start);
		}
		times = getAverage(timeTable);
		path = getAverage(table);
		cout << "Sredni koszt: " << path << endl;
		cout << "Średni czas: " << times << endl << endl;
		delete p;
		p = NULL;
		//---------------------------------------
		file = "gr24.tsp";
		cout << "Dla pliku " << file << endl;
		p = new Parser(file, populationNumber, generationsNumber, mutation);

		//srand(time(NULL));

		for (int i = 0; i < 10; i++) {
			start = clock();
			p->problem->geneticAlgorithm();
			end = clock();
			table[i] = p->problem->finalCost;
			timeTable[i] = ((long)end - (long)start);
		}
		times = getAverage(timeTable);
		path = getAverage(table);
		cout << "Sredni koszt: " << path << endl;
		cout << "Średni czas: " << times << endl << endl;
		delete p;
		p = NULL;
		//---------------------------------------
		Sleep(500);
		file = "br17.atsp";
		cout << "Dla pliku " << file << endl;
		p = new Parser(file, populationNumber, generationsNumber, mutation);

		//srand(time(NULL));

		for (int i = 0; i < 10; i++) {
			start = clock();
			p->problem->geneticAlgorithm();
			end = clock();
			table[i] = p->problem->finalCost;
			timeTable[i] = ((long)end - (long)start);
		}
		times = getAverage(timeTable);
		path = getAverage(table);
		cout << "Sredni koszt: " << path << endl;
		cout << "Średni czas: " << times << endl << endl;
		delete p;
		p = NULL;
		//---------------------------------------
		Sleep(500);
		file = "ftv33.atsp";
		cout << "Dla pliku " << file << endl;
		p = new Parser(file, populationNumber, generationsNumber, mutation);

		//srand(time(NULL));

		for (int i = 0; i < 10; i++) {
			start = clock();
			p->problem->geneticAlgorithm();
			end = clock();
			table[i] = p->problem->finalCost;
			timeTable[i] = ((long)end - (long)start);
		}
		times = getAverage(timeTable);
		path = getAverage(table);
		cout << "Sredni koszt: " << path << endl;
		cout << "Średni czas: " << times << endl << endl;
		delete p;
		p = NULL;
		//---------------------------------------
		Sleep(500);
		file = "ftv44.atsp";
		cout << "Dla pliku " << file << endl;
		p = new Parser(file, populationNumber, generationsNumber, mutation);
		//srand(time(NULL));

		for (int i = 0; i < 10; i++) {
			start = clock();
			p->problem->geneticAlgorithm();
			end = clock();
			table[i] = p->problem->finalCost;
			timeTable[i] = ((long)end - (long)start);
		}
		times = getAverage(timeTable);
		path = getAverage(table);
		cout << "Sredni koszt: " << path << endl;
		cout << "Średni czas: " << times << endl << endl;
		delete p;
		p = NULL;
		//---------------------------------------
	}
	
	//----------------------------------------
	cout << "Press any key to continue...\n";
	_getch();
	return 0;
}



