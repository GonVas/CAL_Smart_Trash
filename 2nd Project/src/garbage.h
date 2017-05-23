/*
 * garbage.h
 *
 *  Created on: 07/04/2017
 *      Author: Diogo
 */

#ifndef GARBAGE_H_
#define GARBAGE_H_

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Garbage {
	int domestic;
	int paper;
	int glass;
	int plastic;
	int nr;
public:
	Garbage(int i);
	int getGarbageTypes() const;
};



#endif /* GARBAGE_H_ */
