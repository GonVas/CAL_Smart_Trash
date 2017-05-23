//
// Created by gonvas on 4/7/17.
//

#ifndef UNTITLED2_DISJOINTSET_HPP
#define UNTITLED2_DISJOINTSET_HPP

#include <vector>

using namespace std;
template<class T>
class DisjointSet{

private:
    T  * parent;
    int rank;

public:

    DisjointSet(T * elem) {
        this->parent = elem;
        this->rank   = 0;
    }

    T * get_parent(){
        return  parent;
    }

    int get_rank(){
        return  rank;
    }

    static void Union( DisjointSet<T> * x, DisjointSet<T> * y) {
        // if x and y are already in the same set (i.e., have the same root or representative)
        if (x->parent == y->parent)
            return ;

        // x and y are not in same set, so we merge them
        if (x->rank < y->rank)
            x->parent = y->parent;
        else if (x->rank > y->rank)
            y->parent = x->parent;
        else
            y->parent = x->parent;
            x->rank = x->rank + 1;
    }

   T Find(DisjointSet<T>  x) {
       return *x.parent;
   }

    static vector<DisjointSet<T>> make_Set(vector<T *> elems){
        vector<DisjointSet<T>> res;

        for(auto elem: elems )
           res.push_back(DisjointSet<T>(elem));

        return res;
    }

};


#endif //UNTITLED2_DISJOINTSET_HPP
