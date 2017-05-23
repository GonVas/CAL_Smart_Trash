/*
 * garbage.c
 *
 *  Created on: 07/04/2017
 *      Author: Diogo
 */

#include "garbage.h"
#include <vector>
#include <queue>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

Garbage::Garbage(int i) {
	if (i == 1)
	{
		domestic = rand() % 100 + 1;
		paper = -1;
		glass = -1;
		plastic = -1;
		nr = 1;
		return;
	}
	else if (i == 2)
	{
		domestic = rand()%100 + 1;
		paper = (rand()%100) + 1;
		glass = -1;
		plastic = -1;
		nr = 2;
		return;
	}
	else if (i == 3)
	{
		domestic = rand()%100 + 1;
		paper = (rand()%100) + 1;
		glass = (rand()%100) + 1;
		plastic = -1;
		nr = 3;
		return;
	}
	else
	{
		domestic = rand()%100 + 1;
		paper = (rand()%100) + 1;
		glass = (rand()%100) + 1;
		plastic = (rand()%100) + 1;
		nr = 4;
		return;
	}

	nr = 0;
}

int Garbage::getGarbageTypes() const {
	return nr;
}

