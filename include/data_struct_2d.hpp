#ifndef DATA_STRUCT_2D_HPP
#define DATA_STRUCT_2D_HPP

#include "graph.hpp"
#include "tools.hpp"
#include<queue>
#include<tuple>
#include <algorithm> 
#include<vector>
#include <variant>
#include <memory>
#include <utility>
#include <cstdlib>

class Label {
public :
    float x;
    float y;
    int pred;
    Label* label_pred;
    bool removed = false;
    bool is_inserted = false;
    
    float getX() const;
    float getY() const;
    int getPred() const;
    Label* getLabelPred() const;
    Label(float _x, float _y, int _pred, Label* lab) {x = _x; y=_y; pred = _pred; label_pred = lab;}
};

class Queue_elt {
public :
    std::tuple<int,Label*> elt = std::make_tuple(0,new Label(0,0,-1,nullptr));
    Queue_elt(int n, Label* label) : elt(std::make_tuple(n, label)) {};
    Queue_elt(){};
    void print();
    int getNode();
    Label* getLabel();

    bool operator<(Queue_elt& other);
};

class Queue_LP {
public :
    std::list<Queue_elt> queue_list;
    Queue_LP(){}
    void add_elt(int n, Label* lab);
    
    Queue_elt first_choice();
    int size();


};


class Label_set {
public :
    std::list<Label> set;

    Label_set(){};

    //Renvoie True si le point a été ajouté et qu'il n'y était pas avant
    bool add_point(float x, float y , int pred, Label* lab);
    void print();
    void add_point_at_end(Label label);
    float calculate_AUC(std::vector<std::vector<float>> &borders, int i);
    Label get_last();

    void add_point_and_update(int x, int y , int pred,Queue_LP &queue,int j);


    
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
    std::vector<bool> node_bool;
    Heap(int N){node_bool = std::vector<bool>(N,false);};
    void push(const Heap_elt& elt);
    Heap_elt top();
    void pop();
    int size();
    bool empty() const;
};



class Queue_NP {
public :
    std::queue<int> queue_list;
    std::vector<bool> node_bool;
    Queue_NP(int N){node_bool = std::vector<bool>(N,false);}
    void add_point(int i);
    int pick();
    int size();


};



class TreeNode {
public : 
    float xb;
    float yb;
    float xt;
    float yt;
    Label* label;  // Pointeur unique vers Label si le noeud est une feuille
    TreeNode* left;
    TreeNode* right;

    // Constructeur pour les noeuds internes
    TreeNode(float xb, float yb, float xt, float yt)
        : xb(xb), yb(yb), xt(xt), yt(yt), label(nullptr), left(nullptr), right(nullptr) {}

    // Constructeur pour les feuilles
    TreeNode(Label* lbl)
        : xb(lbl->getX()), yb(lbl->getY()), xt(lbl->getX()), yt(lbl->getY()), label(lbl), left(nullptr), right(nullptr) {}

    bool isLeaf() const {
        return label != nullptr;
    }
    void print() const;

    std::pair<TreeNode*, bool> insert_label(Label* lab);

    // Interdire la copie
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    // Autoriser le déplacement
    TreeNode(TreeNode&&) = default;
    TreeNode& operator=(TreeNode&&) = default;

};









#endif