#ifndef ALG_BIN_HPP
#define ALG_BIN_HPP

#include "multigraph.hpp"
#include "tools.hpp"

#include<tuple>
#include <algorithm> 
#include<vector>

int choose_node(std::vector<int> &L);
void dijkstra_bin(Multigraph g, int s, int strategy, bool display);



class Label {
public:
    std::vector<int> data; //(x,y,pred)
    Label(int x, int y, int pred){data = {x,y,pred};};
    int getX();
    int getY();
    int getPred();
    void print();

};

class Queue_elt {
public :
    std::tuple<int,Label> elt = std::make_tuple(0,Label(0,0,-1));
    Queue_elt(int n, Label label) : elt(std::make_tuple(n, label)) {};
    Queue_elt(){};
    void print();
    int getNode();
    Label getLabel();

    bool operator<(Queue_elt& other);
};

class Queue {
public :
    std::vector<Queue_elt> queue_list;
    Queue(){}
    void add_elt(int n, Label lab);
    int getNode(int i);
    Label getLabel(int i);
    void print();
    Queue_elt random_choice();
    Queue_elt lexicographic_choice();
    int size();


};
class Label_set {
public :
    std::vector<Label> set;

    Label_set(){};

    //Renvoie True si le point a été ajouté et qu'il n'y était pas avant
    void add_point_and_update(int x, int y , int pred,Queue &queue,int j);

    void print();
    
};

//test

#endif