//============================================================================
// Name        : calfinal.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Graph.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

int id = 1;
int lines = 0;

void pre_kmp(string pattern, vector<int> & prefix) {
	int m = pattern.length();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q < m; q++) {
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = prefix[k];
		if (pattern[k + 1] == pattern[q])
			k = k + 1;
		prefix[q] = k;
	}
}

int kmp(string text, string pattern) {
	int num = 0;
	int m = pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n = text.length();

	int q = -1;
	for (int i = 0; i < n; i++) {
		while (q > -1 && pattern[q + 1] != text[i])
			q = prefix[q];
		if (pattern[q + 1] == text[i]) {
			q++;
		}

		if (q == m - 1) {
			//cout << "pattern occurs with shift" << i - m + 1 << endl;
			num++;
			q = prefix[q];
		}
	}
	return num;
}

int numStringMatching(string filename, string toSearch) {
	ifstream fich(filename.c_str());
	if (!fich) {
		cout << "Erro a abrir ficheiro de leitura\n";
		return 0;
	}

	string line1;
	int num = 0;

	while (!fich.eof()) {
		getline(fich, line1);
		num += kmp(line1, toSearch);
		if (num < 1)
			id++;
		lines++;
	}
	fich.close();
	return num;
}

int editDistance(string pattern, string text)
{
	int n=text.length();
	vector<int> d(n+1);
	int old,neww;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) neww = old;
			else {
				neww = min(old,d[j]);
				neww = min(neww,d[j-1]);
				neww = neww +1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

vector<string> numApproximateStringMatching(string filename,string toSearch)
{
	vector<string> ruasP;
	ifstream fich(filename.c_str());
	if (!fich)
	   { cout << "Erro a abrir ficheiro de leitura\n"; return ruasP; }

	string line1, line2, line3, word1;
	int num=100, nwords=0, nteste=0;

	while (!fich.eof()) {
		getline(fich,line1, ';');
		getline(fich,line2, ';');
		//stringstream s1(line1);
		nteste = editDistance(toSearch,line2);
		getline(fich,line3);

		if (nteste < num)
		{
			num = nteste;
			ruasP.clear();
			ruasP.push_back(line2);
		}
		else if (nteste == num)
		{
			bool control=false;
			for (int i = 0; i < ruasP.size(); i++)
			{
				if (ruasP[i] == line2)
					control = true;
			}

			if (!control)
				ruasP.push_back(line2);
		}
	}
	fich.close();

	return ruasP;
}

int main() {

	int counter=0;
	int choice=0;
	string street;
	string lixo;

	Graph<int> myGraph;
	myGraph.Initialise();

	cout << "Which street do you wish to look for?";
	getline(cin,street);
	cout << "Which type of search do you want? 1 - Exact  2 - Approximate";
	cin >> choice;

	if (choice == 1) {
	int c = numStringMatching("ruas.txt", street);
	bool control = false;
	if (c > 0)
	{
		cout << "Esta rua existe! \n";
		cout << "Vamos, agora, procurar todos os índices de contentores em esquinas formadas com esta rua! \n \n";
		vector<int> vec = myGraph.garbageCorners(street);

		if (vec.size()!=0) {

		cout << "* * * * * * * * * * * * " << "      ________________    ___/-" << "\\" << "___     ___/-" << "\\" << "___     ___/-" << "\\" << "___\n";
		cout << "*                     * " << "     / /             ||  |---------|   |---------|   |---------|\n";
		cout << "*                     * " << "    / /              ||   |       |     |       |     |       |\n";
		cout << "*    PESQUISA EXATA   * " << "   / /             __||   | | | | |     | | | | |     | | | | |\n";
		cout << "*                     * " << "  / /             I  ||   | | | | |     | | | | |     | | | | |\n";
		cout << "*     CONTENTORES     * " << " (-------------------||   | | | | |     | | | | |     | | | | |\n";
		cout << "*                     * " << " ||               == ||   |_______|     |_______|     |_______|\n";
		cout << "*                     * " << " ||                  | =============================================\n";
		cout << "*                     * " << " ||          ____    |                                ____      |\n";
		cout << "* ******************* * " << "( | o      / ____ " << "\\" << "                                 / ____ "<< "\\" << "    |)\n";
		cout << "*                     * " << " ||      / / . . \ " << "\\" << "                               / / . . " << "\\" << " " << "\\" << "   |\n";
		cout << "*  Numero     Indice  * " << "[ |_____| | .   . | |____________________________| | .   . | |__]\n";
		cout << "*                     * " << "          | .   . |                                | .   . |\n";
		cout << "* ******************* * " << "           " << "\\" << "_____/                                  " << "\\" << "_____/\n";


		for (int i = 0; i < vec.size(); i++)
		{
			counter++;
			cout << "*"<< setw(5) << counter << ": ";
			cout << setw(10) << vec[i]<< setw(7) << "* \n";
		}
		cout << "* * * * * * * * * * * *\n";
		} else
			{
			cout << "Não há nenhum contentor numa esquina formada com essa rua!";
			}
	} else
	{
		cout << "Esta Rua n�o existe!";
	}
	} else if (choice == 2) {
		vector<string> teste = numApproximateStringMatching("ruas.txt", street);

		cout << "\n \n";
		counter=0;
		for (int i = 0; i < teste.size(); i++)
		{
			vector<int> vec1 = myGraph.garbageCorners(teste[i]);
			cout << "*" << teste[i] << ":" << "*\n";

			if (vec1.size()!=0) {

					cout << "* * * * * * * * * * * * " << "      ________________    ___/-" << "\\" << "___     ___/-" << "\\" << "___     ___/-" << "\\" << "___\n";
					cout << "*                     * " << "     / /             ||  |---------|   |---------|   |---------|\n";
					cout << "*                     * " << "    / /              ||   |       |     |       |     |       |\n";
					cout << "* PESQUISA APROXIMADA * " << "   / /             __||   | | | | |     | | | | |     | | | | |\n";
					cout << "*                     * " << "  / /             I  ||   | | | | |     | | | | |     | | | | |\n";
					cout << "*     CONTENTORES     * " << " (-------------------||   | | | | |     | | | | |     | | | | |\n";
					cout << "*                     * " << " ||               == ||   |_______|     |_______|     |_______|\n";
					cout << "*                     * " << " ||                  | =============================================\n";
					cout << "*                     * " << " ||          ____    |                                ____      |\n";
					cout << "* ******************* * " << "( | o      / ____ " << "\\" << "                                 / ____ "<< "\\" << "    |)\n";
					cout << "*                     * " << " ||      / / . . \ " << "\\" << "                               / / . . " << "\\" << " " << "\\" << "   |\n";
					cout << "*  Numero     Indice  * " << "[ |_____| | .   . | |____________________________| | .   . | |__]\n";
					cout << "*                     * " << "          | .   . |                                | .   . |\n";
					cout << "* ******************* * " << "           " << "\\" << "_____/                                  " << "\\" << "_____/\n";
			} else cout << "Não há nenhum contentor numa esquina formada com essa rua!";
			for (int j=0; j < vec1.size(); j++)
			{
				counter++;
				cout << "*"<< setw(5) << counter << ": ";
				cout << setw(10) << vec1[j]<< setw(7) << "* \n";
			}
			cout << "* * * * * * * * * * * *\n";

			cout << "\n";
		}
		}
	return 0;
}
