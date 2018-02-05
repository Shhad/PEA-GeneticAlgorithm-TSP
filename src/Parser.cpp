//Autor: Filip Baszak
#include "stdafx.h"
#include "Parser.h"
#include "GeneticA.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <list>
#include <chrono>
#include <string>
#include <ctime>
#include <sstream>
#include <utility>
#include <vector>
#include <math.h>

using namespace std;

Parser::Parser()
{
	doData();
}

Parser::Parser(string txt, int pN)
{
	doData(txt, pN);
}

Parser::Parser(string txt, int pN, int gN, double mN)
{
	doData(txt, pN, gN, mN);
}


Parser::~Parser()
{
	delete problem;
}

void Parser::doData(string txt, int pN) {
	//ifstream file;
	//string txt;
	//cout << "Podaj nazwe pliku: ";
	//cin >> txt;
	cout << endl;
	string a;
	string b;
	string edgeType = "NULL";
	problem = NULL;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			problem = new GeneticA(z, pN);
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			problem = new GeneticA(z, pN);
			z = 0;
		}
		if (a == "EDGE_WEIGHT_TYPE:") {
			file >> b;
			cout << b << "to nasz tryb krawedzi" << endl;
			edgeType = b;
			if (edgeType == "EXPLICIT") {
				file >> b;
				if (b == "EDGE_WEIGHT_FORMAT") {
					file >> b;
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
				if (b == "EDGE_WEIGHT_FORMAT:") {
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
			}
		}
		if (a == "EDGE_WEIGHT_TYPE") {
			file >> b;
			file >> b;
			cout << b << "to nasz typ krawedz" << endl;
			edgeType = b;
			if (edgeType == "EXPLICIT") {
				file >> b;
				if (b == "EDGE_WEIGHT_FORMAT") {
					file >> b;
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
				if (b == "EDGE_WEIGHT_FORMAT:") {
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
			}
		}
		//NODE_COORD_SECTION OR EDGE_WEIGHT_SECTION
		if (a == "EDGE_WEIGHT_SECTION" || a == "NODE_COORD_SECTION") {
			while (a != "EOF") {
				if (edgeType == "GEO") {

				}
				if (edgeType == "EUC_2D") {
					cout << endl << "jestem w euc2d" << endl;
					int *x = new int[problem->verN];
					int *y = new int[problem->verN];
					for (int i = 0; i < problem->verN; i++) {
						file >> a;
						if (a == "EOF") {
							file >> a;
							break;
						}
						cout << a << endl;
						file >> a;
						cout << stoi(a) << endl;
						x[i] = stoi(a);
						file >> a;
						cout << stoi(a) << endl;
						y[i] = stoi(a);
					}
					int xd = 0;
					int yd = 0;
					int dij = 0;
					for (int i = 0; i < problem->verN; i++) {
						cout << "x[" << i << "] wynosi " << x[i] << "a, y[" << i << "] wynosi " << y[i] << endl;
						for (int j = 0; j < problem->verN; j++) {
							if (i == j) {
								problem->matrix[i][j] = -1;
							}
							else {
								xd = x[i] - x[j];
								yd = y[i] - y[j];
								dij = nearbyint(sqrt(xd*xd + yd*yd));
								//cout << "Odleglosc z " << i << " do " << j << " wynosi " << dij << endl;
								problem->matrix[i][j] = dij;
							}
						}
					}
					delete x;
					delete y;
					a = "EOF";
				}
				if (edgeType == "LOWER_DIAG_ROW") {
					for (int i = 0; i <= counter; i++) {
						file >> a;
						if (a != "EOF") {
							problem->matrix[counter][i] = stoi(a);
							problem->matrix[i][counter] = stoi(a);
						}
					}
					counter++;
				}
				if (edgeType == "FULL_MATRIX") {
					for (int i = 0; i < problem->verN; i++) {
						file >> a;
						if (a != "EOF") {
							problem->matrix[counter][i] = stoi(a);
						}
					}
					counter++;
				}

			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	//problem->printMatrix();
	cout << endl;
	file.close();
}

void Parser::doData() {
	//ifstream file;
	string txt;
	int pN;
	int gN;
	double mN;
	cout << "Podaj nazwe pliku: ";
	cin >> txt;
	cout << "Podaj wielkosc populacji: ";
	cin >> pN;
	cout << "Podaj ilosc pokolen: ";
	cin >> gN;
	cout << "Podaj wspolczynnik mutacji(double): ";
	cin >> mN;
	cout << endl;
	string a;
	string b;
	string edgeType = "NULL";
	problem = NULL;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			problem = new GeneticA(z, pN,gN,mN);
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			problem = new GeneticA(z, pN, gN, mN);
			z = 0;
		}
		if (a == "EDGE_WEIGHT_TYPE:") {
			file >> b;
			cout << b << "to nasz tryb krawedzi" << endl;
			edgeType = b;
			if (edgeType == "EXPLICIT") {
				file >> b;
				if (b == "EDGE_WEIGHT_FORMAT") {
					file >> b;
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
				if (b == "EDGE_WEIGHT_FORMAT:") {
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
			}
		}
		if (a == "EDGE_WEIGHT_TYPE") {
			file >> b;
			file >> b;
			cout << b << "to nasz typ krawedz" << endl;
			edgeType = b;
			if (edgeType == "EXPLICIT") {
				file >> b;
				if (b == "EDGE_WEIGHT_FORMAT") {
					file >> b;
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
				if (b == "EDGE_WEIGHT_FORMAT:") {
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
			}
		}
		//NODE_COORD_SECTION OR EDGE_WEIGHT_SECTION
		if (a == "EDGE_WEIGHT_SECTION" || a == "NODE_COORD_SECTION") {
			while (a != "EOF") {
				if (edgeType == "GEO") {
					cout << endl << "jestem w geo" << endl;
				}
				if (edgeType == "EUC_2D") {
					cout << endl << "jestem w euc2d" << endl;
					int *x = new int[problem->verN];
					int *y = new int[problem->verN];
					for (int i = 0; i < problem->verN; i++) {
						file >> a;
						if (a == "EOF") {
							file >> a;
							break;
						}
						cout << a << endl;
						file >> a;
						cout << stoi(a) << endl;
						x[i] = stoi(a);
						file >> a;
						cout << stoi(a) << endl;
						y[i] = stoi(a);
					}
					int xd = 0;
					int yd = 0;
					int dij = 0;
					for (int i = 0; i < problem->verN; i++) {
						cout << "x[" << i << "] wynosi " << x[i] << "a, y[" << i << "] wynosi " << y[i] << endl;
						for (int j = 0; j < problem->verN; j++) {
							if (i == j) {
								problem->matrix[i][j] = -1;
							}
							else {
								xd = x[i] - x[j];
								yd = y[i] - y[j];
								dij = nearbyint(sqrt(xd*xd + yd*yd));
								//cout << "Odleglosc z " << i << " do " << j << " wynosi " << dij << endl;
								problem->matrix[i][j] = dij;
							}
						}
					}
					delete x;
					delete y;
					a = "EOF";
				}
				if (edgeType == "LOWER_DIAG_ROW") {
					cout << endl << "jestem w lower tra" << endl;
					for (int i = 0; i <= counter; i++) {
						file >> a;
						if (a != "EOF") {
							problem->matrix[counter][i] = stoi(a);
							problem->matrix[i][counter] = stoi(a);
						}
					}
					counter++;
				}
				if (edgeType == "FULL_MATRIX") {
					cout << endl << "jestem w full matrix" << endl;
					for (int i = 0; i < problem->verN; i++) {
						file >> a;
						if (a != "EOF") {
							problem->matrix[counter][i] = stoi(a);
						}
					}
					counter++;
				}

			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	//problem->printMatrix();
	cout << endl;
	file.close();
}

void Parser::doData(string txt, int pN, int gN, double mN) {
	//ifstream file;
	//string txt;
	//cout << "Podaj nazwe pliku: ";
	//cin >> txt;
	cout << endl;
	string a;
	string b;
	string edgeType = "NULL";
	problem = NULL;
	int z = 0;
	int stop = 0;
	int counter = 0;
	string line;
	istringstream iss;
	file.open(txt.c_str());
	while (file.good()) {
		file >> a;
		cout << a << endl;
		if (a == "DIMENSION:") {
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			problem = new GeneticA(z, pN);
			z = 0;
		}
		if (a == "DIMENSION") {
			file >> b;
			file >> b;
			cout << b << "to nasze wierzcholki" << endl;
			z = stoi(b);
			problem = new GeneticA(z, pN);
			z = 0;
		}
		if (a == "EDGE_WEIGHT_TYPE:") {
			file >> b;
			cout << b << "to nasz tryb krawedzi" << endl;
			edgeType = b;
			if (edgeType == "EXPLICIT") {
				file >> b;
				if (b == "EDGE_WEIGHT_FORMAT") {
					file >> b;
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
				if (b == "EDGE_WEIGHT_FORMAT:") {
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
			}
		}
		if (a == "EDGE_WEIGHT_TYPE") {
			file >> b;
			file >> b;
			cout << b << "to nasz typ krawedz" << endl;
			edgeType = b;
			if (edgeType == "EXPLICIT") {
				file >> b;
				if (b == "EDGE_WEIGHT_FORMAT") {
					file >> b;
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
				if (b == "EDGE_WEIGHT_FORMAT:") {
					file >> b;
					edgeType = b;
					cout << "zmiana typu krawedzi na: " << edgeType << endl;
				}
			}
		}
		//NODE_COORD_SECTION OR EDGE_WEIGHT_SECTION
		if (a == "EDGE_WEIGHT_SECTION" || a == "NODE_COORD_SECTION") {
			while (a != "EOF") {
				if (edgeType == "GEO") {

				}
				if (edgeType == "EUC_2D") {
					cout << endl << "jestem w euc2d" << endl;
					int *x = new int[problem->verN];
					int *y = new int[problem->verN];
					for (int i = 0; i < problem->verN; i++) {
						file >> a;
						if (a == "EOF") {
							file >> a;
							break;
						}
						cout << a << endl;
						file >> a;
						cout << stoi(a) << endl;
						x[i] = stoi(a);
						file >> a;
						cout << stoi(a) << endl;
						y[i] = stoi(a);
					}
					int xd = 0;
					int yd = 0;
					int dij = 0;
					for (int i = 0; i < problem->verN; i++) {
						cout << "x[" << i << "] wynosi " << x[i] << "a, y[" << i << "] wynosi " << y[i] << endl;
						for (int j = 0; j < problem->verN; j++) {
							if (i == j) {
								problem->matrix[i][j] = -1;
							}
							else {
								xd = x[i] - x[j];
								yd = y[i] - y[j];
								dij = nearbyint(sqrt(xd*xd + yd*yd));
								//cout << "Odleglosc z " << i << " do " << j << " wynosi " << dij << endl;
								problem->matrix[i][j] = dij;
							}
						}
					}
					delete x;
					delete y;
					a = "EOF";
				}
				if (edgeType == "LOWER_DIAG_ROW") {
					for (int i = 0; i <= counter; i++) {
						file >> a;
						if (a != "EOF") {
							problem->matrix[counter][i] = stoi(a);
							problem->matrix[i][counter] = stoi(a);
						}
					}
					counter++;
				}
				if (edgeType == "FULL_MATRIX") {
					for (int i = 0; i < problem->verN; i++) {
						file >> a;
						if (a != "EOF") {
							problem->matrix[counter][i] = stoi(a);
						}
					}
					counter++;
				}

			}
		}
	}
	cout << "Udalo sie utworzyc tablice elementow. \n";
	//problem->printMatrix();
	cout << endl;
	file.close();
}