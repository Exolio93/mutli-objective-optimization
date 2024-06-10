#ifndef ALG_BIN_HPP
#define ALG_BIN_HPP

#include "multigraph.hpp"
#include "tools.hpp"

#include<tuple>
#include <algorithm> 
#include<vector>

int choose_node(std::vector<int> &L);
void dijkstra_bin(Multigraph g, int s, int strategy, bool display);

class Queue {
public :
    std::vector<std::vector<int>> queue_list;
    Queue(){}
    void add_point(int i);
    void remove_point(int i);
    void print();
    int random_choice();
    int max_it_choice();
    int size();


};

class Label {
public :
    int x;
    int y;
    int pred;

    int getX() const;
    int getY() const;
    int getPred() const;

    Label(int _x, int _y, int _pred) {x = _x; y=_y; pred = _pred;}
};

class Label_set {
public :
    std::list<Label> set;

    Label_set(){};

    //Renvoie True si le point a été ajouté et qu'il n'y était pas avant
    bool add_point(int x, int y , int pred);
    void add_set(Label_set &lab_i, Arc &Wij);
    void print();
    void add_point_at_end(Label label);
    Label get_last();


    
};

void labels_update(std::vector<Label_set> &labels, Arc &Wij,std::vector<int> &queue);

void labels_update2(std::vector<Label_set> &labels, Arc &Wij,std::vector<int> &queue);
bool add_pareto_set(std::vector<Label_set> &labs, Arc &Wij);





#endif