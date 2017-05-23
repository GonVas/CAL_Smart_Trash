/*
 * camioes.h
 *
 *  Created on: 09/04/2017
 *      Author: Diogo
 */

#ifndef CAMIOES_H_
#define CAMIOES_H_

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Camioes {
	bool domestic;
	bool paper;
	bool glass;
	bool plastic;
	int nr;
	int capacity;

public:
	Camioes(int i);
	int getCamioesTypes() const;
};






#endif /* CAMIOES_H_ */
