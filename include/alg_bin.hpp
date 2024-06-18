#ifndef ALG_BIN_HPP
#define ALG_BIN_HPP

#include "multigraph.hpp"
#include "tools.hpp"
#include<queue>
#include<tuple>
#include <algorithm> 
#include<vector>

std::vector<std::vector<float>> dijkstra_1D(Multigraph g, int s);
void dijkstra_bin(Multigraph g, int s, int strategy, bool display);
void dijkstra_AUC(Multigraph g, int s, bool display);


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

class Queue_elt {
public :
    int n;
    float auc;
    Label_set* l;

    Queue_elt(int i, Label_set &l_set, std::vector<std::vector<float>> &borders) : n(i), l(&l_set), auc(l_set.calculate_AUC(borders, i)) {};

    bool operator<(const Queue_elt& other) const;
};


class Queue_priority {
public:
    std::priority_queue<Queue_elt> pq;

    Queue_priority(){};
    void push(const Queue_elt& elt);
    Queue_elt top();
    void pop();
    int size();
    bool empty() const;
};



class Queue {
public :
    std::vector<int> queue_list;
    Queue(){}
    void add_point(int i);
    void remove_point(int i);
    void print();
    int random_choice();
    int first_choice();
    int size();


};



void labels_update(std::vector<Label_set> &labels, Arc &Wij,std::vector<int> &queue);
void labels_update2(std::vector<Label_set> &labels, Arc &Wij,std::vector<int> &queue);
void labels_update2_priority(std::vector<Label_set> &labels, Arc &Wij,Queue_priority &queue, std::vector<std::vector<int>> &borders);

bool add_pareto_set(std::vector<Label_set> &labs, Arc &Wij);





#endif