//Autor: Filip Baszak
#pragma once
#include "stdafx.h"
#include "GeneticA.h"
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

class Parser {
public:
	std::ifstream file;
	GeneticA *problem;
	void doData(string txt, int pN);
	void doData(string txt, int pN, int gN, double mN);
	void doData();
	Parser();
	Parser(string txt, int pN);
	Parser(string txt, int pN, int gN, double mN);
	~Parser();
};

