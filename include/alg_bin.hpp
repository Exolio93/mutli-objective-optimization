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

class Label_bin {
public :
    std::vector<std::tuple<std::tuple<int,int>, int>> set;

    Label_bin(){};

    int getX(int i);
    int getY(int i);
    int getPred(int i);

    //Renvoie True si le point a été ajouté et qu'il n'y était pas avant
    bool add_point(int x, int y , int pred);

    void print();
    
};

void labels_update(std::vector<Label_bin> &labels, int i, int j, Arc &Wij,std::vector<int> &queue);


#endif