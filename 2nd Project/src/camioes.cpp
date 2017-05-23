/*
 * camioes.cpp
 *
 *  Created on: 09/04/2017
 *      Author: Diogo
 */

#include "camioes.h"
#include <vector>
#include <queue>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

Camioes::Camioes(int i) {
	if (i == 1)
	{
		domestic = true;
		paper = false;
		glass = false;
		plastic = false;
		nr = 1;
		capacity =  rand()%5000 + 1;
		return;
	}
	else if (i == 2)
	{
		domestic = true;
		paper = true;
		glass = false;
		plastic = false;
		nr = 2;
		return;
	}
	else if (i == 3)
	{
		domestic = true;
		paper = true;
		glass = true;
		plastic = false;
		nr = 3;
		return;
	}
	else
	{
		domestic = true;
		paper = true;
		glass = true;
		plastic = true;
		nr = 4;
		return;
	}

	nr = 0;
}

int Camioes::getCamioesTypes() const {
	return nr;
}
