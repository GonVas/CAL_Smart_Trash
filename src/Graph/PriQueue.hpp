//
// Created by gonvas on 3/31/17.
//

#ifndef UNTITLED2_PRIQUEUE_HPP
#define UNTITLED2_PRIQUEUE_HPP

#include <algorithm>
#include <queue>
#include <vector>
#include <memory>

template<class T, class K>
struct value {
    value(T elem, K priority) : elem(elem), priority(priority) {}

    T elem;
    K priority;
};

template<class T, class K>
struct comparator{
    bool less;
    comparator(bool less) { this->less = less;}

    bool operator()(const value<T,K> &lhs, const value<T,K> &rhs){
        if(!less)
            if(lhs.priority < rhs.priority)
                return true;
            else
                return false;
        else
            if(lhs.priority > rhs.priority)
                return true;
            else
                return false;
    }
};

template<class T, class K>
class PriQueue
{
public:
    PriQueue<T, K>();

    void addWithPriority(T elem, K criteria);
    bool decreasePriority(T elem, K criteria);
    T extractTop();
    T peakTop();

    int size();
    bool isLess_op() const;
    void setLess_op(bool less_op);

    bool eraseElem(T elem);

    //Testing
    bool isHeap();

private:
    std::vector<value<T,K>> data;
    bool less_op;

    comparator<T,K> comp_func = comparator<T,K>(true);

    void remake();

    //T default_T;
};
template<class T, class K>
void PriQueue<T,K>::addWithPriority(T elem, K criteria) {
    value<T, K> v(elem, criteria);
    this->data.push_back(v);
    std::push_heap(this->data.begin(), this->data.end(), this->comp_func);
}

template<class T, class K>
PriQueue<T,K>::PriQueue(/*T default_T*/) {
    this->comp_func = comparator<T,K>(true);
}

template<class T, class K>
T PriQueue<T,K>::extractTop() {
    T res = this->data.at(0).elem;
    std::pop_heap(this->data.begin(), this->data.end(), this->comp_func);
    this->data.pop_back();
    return res;
}

template<class T, class K>
bool PriQueue<T,K>::decreasePriority(T elem, K criteria) {
    for (int i = 0; i < this->data.size(); ++i) {
        if(this->data.at(i).elem == elem) {
            this->data.erase(this->data.begin() + i);
            this->data.push_back(value<T,K>(elem,criteria));
            this->remake();
            return true;
        }
    }
    return false;
}

template<class T, class K>
bool PriQueue<T,K>::isLess_op() const {
    return less_op;
}

template<class T, class K>
void PriQueue<T,K>::setLess_op(bool less_op) {
    PriQueue::less_op = less_op;
    this->comp_func.less = less_op;
}

template<class T, class K>
T PriQueue<T,K>::peakTop() {
    if(this->data.size() > 0)
    return this->data.at(0).elem;
}

template<class T, class K>
int PriQueue<T,K>::size() {
    return this->data.size();
}

template<class T, class K>
void PriQueue<T,K>::remake() {
    std::make_heap(this->data.begin(), this->data.end(), this->comp_func);
}

template<class T, class K>
bool PriQueue<T,K>::isHeap() {
    return std::is_heap(this->data.begin(), this->data.end(), this->comp_func);
}

template<class T, class K>
bool PriQueue<T,K>::eraseElem(T elem) {

    for (int i = 0; i < this->data.size(); ++i)
        if((this->data.at(i)).elem == elem){
            this->data.erase(this->data.begin() + i);
            return true;
        }



    return false;
}

#endif //UNTITLED2_PRIQUEUE_HPP
