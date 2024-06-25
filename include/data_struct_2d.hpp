#ifndef DATA_STRUCT_2D_HPP
#define DATA_STRUCT_2D_HPP

#include "graph.hpp"
#include "tools.hpp"
#include<queue>
#include<tuple>
#include <algorithm> 
#include<vector>

class Label {
public :
    float x;
    float y;
    int pred;
    
    float getX() const;
    float getY() const;
    int getPred() const;

    Label(float _x, float _y, int _pred) {x = _x; y=_y; pred = _pred;}
};

class Label_set {
public :
    std::list<Label> set;

    Label_set(){};

    //Renvoie True si le point a été ajouté et qu'il n'y était pas avant
    bool add_point(float x, float y , int pred);
    void print();
    void add_point_at_end(Label label);
    float calculate_AUC(std::vector<std::vector<float>> &borders, int i);
    Label get_last();


    
};

class Heap_elt {
public :
    int n;
    float auc;
    Label_set* l;

    Heap_elt(int i, Label_set &l_set, std::vector<std::vector<float>> &borders) : n(i), l(&l_set), auc(l_set.calculate_AUC(borders, i)) {};

    bool operator<(const Heap_elt& other) const;
};


class Heap {
public:
    std::priority_queue<Heap_elt> pq;

    Heap(){};
    void push(const Heap_elt& elt);
    Heap_elt top();
    void pop();
    int size();
    bool empty() const;
};



class Queue {
public :
    std::vector<int> queue_list;
    std::vector<bool> node_bool;
    Queue(int N){node_bool = std::vector<bool>(N,false);}
    void add_point(int i);
    void print();
    int pick();
    int size();


};

#endif