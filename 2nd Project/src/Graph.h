/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include "garbage.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;

template<class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool visited;
	////////////////
	double x;
	double y;
	Garbage amount;
	bool garagem;
	bool recolha;
	/////////////////
	void addEdge(Vertex<T> *dest, long id, double w, long rua, string rN);
	bool removeEdgeTo(Vertex<T> *d);
	bool findEdgeTo(Vertex<T> *d, string rua);
public:
	Vertex(T in, double x, double y);
	friend class Graph<T> ;
	void setGarbage(int i);
	T getInfo() const;
};

template<class T>
void Vertex<T>::setGarbage(int i) {
	Garbage temp(i);
	this->amount = temp;
}

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		} else
			it++;
	}
	return false;
}

template<class T>
bool Vertex<T>::findEdgeTo(Vertex<T> *d, string rua) {
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			if (it->ruaName != rua)
				return false;
		}

		it++;
	}

	return true;
}

template<class T>
Vertex<T>::Vertex(T in, double x, double y) :
		info(in), visited(false), x(x), y(y), amount(Garbage(0)), garagem(0), recolha(
				0) {
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, long id, double w, long rua,
		string rN) {
	Edge<T> edgeD(dest, id, w, rua, rN);
	adj.push_back(edgeD);
}

template<class T>
class Edge {
	Vertex<T> * dest;
	long id;
	long rua;
	string ruaName;
	double weight;
public:
	Edge(Vertex<T> *d, long id, double w, long r, string rN);
	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, long id, double w, long r, string rN) :
		dest(d), id(id), weight(w), rua(r), ruaName(rN) {
}

template<class T>
class Graph {
	int id_max;

	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
	void conectivity(Vertex<T> *v, vector<T> &res);
public:
	void Initialise();
	void setGarb(const T &in, int garb);
	void setPlace(const T &in, int place);
	bool addVertex(const T &in, double x, double y);
	bool addEdge(const T &sourc, const T &dest, long id, long rua, string rN);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
	vector<T> conectivity();
	vector<T> garbageCorners(string rua);
};

/////////////////
template<class T>
void Graph<T>::Initialise() {
	this->id_max = 1;

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");
	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string line;

	int idNo = 0;
	double X = 0;
	double Y = 0;
	double ctymax = 41.013;
	double ctymin = 40.99774;
	double ctxmax = -8.634513;
	double ctxmin = -8.645487;
	double ctmsize = 2000;
	double dify = ctymax - ctymin;
	double difx = ctxmax - ctxmin;
	bool failed;
	int garbage;
	int thing;
	int times = 0;

	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		string data;

		linestream >> idNo;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> Y;

		double temp = Y - ctymin;
		Y = ctmsize * (temp / dify);

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> X;

		double temp2 = X - ctxmin;
		X = ctmsize * (temp2 / difx);

		failed = this->addVertex(idNo, X, Y);
		/*if (!failed)
			cout << idNo << "\n";
		else
			cout << idNo << " top" << "\n";*/

		thing = rand() % 2;

		if (thing == 1) {
			garbage = (rand() % 4) + 1;
			this->setGarb(idNo, garbage);
		} else if (times < 2) {
			this->setPlace(idNo, times);
			times++;
		}
	}

	inFile.close();

	//Ler o ficheiro ruas.txt
	inFile.open("ruas.txt");

	int idAresta = 0;
	vector<int> temp;

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	string rua;
	string sentidos;
	//int idrua;
	string idruaT;
	vector<string> temp1;
	vector<string> temp2;
	vector<int> temp3;
	int i = 0;
	int rcount = 0;

	while (!inFile.eof()) {

		std::getline(inFile, idruaT, ';');
		//idrua = atoi(idruaT.c_str());
		temp2.push_back(idruaT);
		std::getline(inFile, rua, ';');
		temp1.push_back(rua);
		std::getline(inFile, sentidos);
		//cout << idruaT << "\n";
		//cout << rua << "\n";
		//cout << sentidos << "\n";

		if (sentidos == "True") {
			temp.push_back(atoi(idruaT.c_str()));
			//cout << idruaT << " add way" << "\n";
		}

		idruaT = "";
		rua = "";
		sentidos = "";
	}

	for (rcount; rcount < temp2.size(); rcount++) {
		temp3.push_back(atoi(temp2[rcount].c_str()));
	}
	for (rcount = 0; rcount < temp2.size(); rcount++) {
		//cout << temp3[rcount] << "  ";
	}
	rcount = 0;

	inFile.close();

	//Ler o ficheiro arestas.txt
	inFile.open("aresta.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idNoOrigem;
	int idNoDestino;
	int idcount = 0;
	int id;
	int snt = 0;
	bool control;

	while (std::getline(inFile, line)) {

		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;

		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		std::getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> idNoDestino;

		idcount++;
		this->id_max++;

		for (int j = 0; j < temp.size(); j++) {
			if (idAresta == temp[j])
				snt = 1;
		}

		for (rcount; rcount < temp3.size(); rcount++) {
			if (temp3[rcount] == idAresta) {
				control = true;
				break;
			}
		}

		/*if (control == false)
			cout << "Erro \n";*/

		if (snt == 1) {
			failed = this->addEdge(idNoDestino, idNoOrigem, idcount, idAresta,
					temp1[rcount]);
			//if (!failed)
				//cout << idAresta << " failed" << "\n";
		}

		failed = this->addEdge(idNoOrigem, idNoDestino, idcount, idAresta,
				temp1[rcount]);

		//if (!failed)
			//cout << idAresta << " failed" << "\n";

		rcount = 0;
		control = false;
		snt = 0;
	}

	inFile.close();

}

template<class T>
void Graph<T>::setGarb(const T &in, int garb) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			(*it)->setGarbage(garb);
}

template<class T>
void Graph<T>::setPlace(const T &in, int place) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			if (place == 0) {
				(*it)->garagem = true;
				(*it)->recolha = false;
			} else {
				(*it)->recolha = true;
				(*it)->garagem = false;
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::conectivity() {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;

	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false) {
			if ((*it)->garagem == true) {
				//cout << "\n";
				//cout << (*it)->info << "\n";
				conectivity(*it, res);
			}
		}
	return res;
}

template<class T>
void Graph<T>::conectivity(Vertex<T> *v, vector<T> &res) {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	if (!(v->adj.empty()))
		//cout << it->ruaName << "\n";

	for (; it != ite; it++) {
		if (it->dest->visited == false)
			conectivity(it->dest, res);
	}
}

template<class T>
vector<T> Graph<T>::garbageCorners(string rua) {
	vector<string> temp;
	vector<T> res;
	bool igual = false;
	bool control = false;
	int counter = 0;

	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		typename vector<Edge<T> >::iterator it1 = ((*it)->adj).begin();
		typename vector<Edge<T> >::iterator it1e = ((*it)->adj).end();

		if (!((*it)->adj.empty())) {
			if (((*it)->amount).getGarbageTypes() != 0) {
				for (; it1 != it1e; it1++) {
					if (counter == 0) {
						temp.push_back(it1->ruaName);
						if (it1->ruaName == rua)
							control = true;
						counter++;
					}

					for (int i = 0; i < temp.size(); i++) {
						if (temp[i] == it1->ruaName) {
							igual == true;
							break;
						}
					}

					if (!igual)
						temp.push_back(it1->ruaName);
					if (it1->ruaName == rua)
						control = true;
				}

				if ((temp.size() < 2) && control == true) {
					typename vector<Vertex<T>*>::iterator it2 =
							vertexSet.begin();
					typename vector<Vertex<T>*>::iterator it2e =
							vertexSet.end();
					for (; it2 != it2e; it2++) {
						igual = (*it2)->findEdgeTo(*it, rua);
					}

					if (!igual)
						res.push_back((*it)->info);
				} else if (control) {
					res.push_back((*it)->info);
				}
			}
		}
		temp.clear();
		igual = false;
		control = false;
		counter = 0;
	}

	return res;
}

/////////////////

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
bool Graph<T>::addVertex(const T &in, double x, double y) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	Vertex<T> *v1 = new Vertex<T>(in, x, y);
	vertexSet.push_back(v1);
	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, long id, long rua,
		string rN) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vS->addEdge(vD, id,
			sqrt(
					(vS->x - vD->x) * (vS->x - vD->x)
							+ (vS->y - vD->y) * (vS->y - vD->y)), rua, rN);
	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	return vS->removeEdgeTo(vD);
}

template<class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false)
			dfs(it->dest, res);
}

template<class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template<class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop();
		l++;
		int nChildren = 0;
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

#endif /* GRAPH_H_ */
