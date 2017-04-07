//
// Created by gonvas on 4/7/17.
//

#ifndef UNTITLED2_DISJOINTSET_HPP
#define UNTITLED2_DISJOINTSET_HPP

template<class T>
class DisjointSet{

private:
    T  * parent;
    int rank;

    vector<T*> elements;
public:

    DisjointSet(vector<T> elemns) {
        this->parent = &elem;
        this->rank   = 0;
    }

    bool Union( DisjointSet<T> x, DisjointSet<T> y) {
        auto xRoot = Find(x);
        auto yRoot = Find(y);
        // if x and y are already in the same set (i.e., have the same root or representative)
        if (xRoot == yRoot)
            return true;

        // x and y are not in same set, so we merge them
        if (xRoot.rank < yRoot.rank)
            xRoot.parent = yRoot;
        else if (xRoot.rank > yRoot.rank)
            yRoot.parent = xRoot;
        else
            yRoot.parent = xRoot;
            xRoot.rank = xRoot.rank + 1;
    }

   T Find(T x) {
       if (this->parent == &x)
           return x;
       else
           return this->Find(&x.parent);
   }

    /*
    T FindRoot(DisjointSet<T> x)
    if (this.parent == x.parent)
    return x.parent;
    else
    return this.Find(DiskointSet<T>(x.parent));

    bool operator==(const DisjointSet<T> & rhs ){
        return (this->parent == rhs.parent)
    }*/

};


#endif //UNTITLED2_DISJOINTSET_HPP
