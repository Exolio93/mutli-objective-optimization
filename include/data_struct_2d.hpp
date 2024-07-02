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

class Label {
public :
    float x;
    float y;
    int pred;
    Label* label_pred;
    
    float getX() const;
    float getY() const;
    int getPred() const;
    Label* getLabelPred() const;
    Label(float _x, float _y, int _pred, Label* lab) {x = _x; y=_y; pred = _pred; label_pred = lab;}
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



class Queue {
public :
    std::queue<int> queue_list;
    std::vector<bool> node_bool;
    Queue(int N){node_bool = std::vector<bool>(N,false);}
    void add_point(int i);
    int pick();
    int size();


};



struct TreeNode {
    std::pair<int, int> coords;
    std::unique_ptr<Label> label;  // Pointeur unique vers Label si le noeud est une feuille
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    // Constructeur pour les noeuds internes
    TreeNode(int x, int y)
        : coords(std::make_pair(x, y)), label(nullptr), left(nullptr), right(nullptr) {}

    // Constructeur pour les feuilles
    TreeNode(const Label& lbl)
        : coords(std::make_pair(lbl.getX(), lbl.getY())), label(std::make_unique<Label>(lbl)), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    std::shared_ptr<TreeNode> root;

    BinaryTree() : root(nullptr) {}

    // Méthode pour ajouter un noeud interne
    void addInternalNode(int x, int y, std::shared_ptr<TreeNode> parent, bool isLeft);

    // Méthode pour ajouter une feuille
    void addLeaf(const Label& lbl, std::shared_ptr<TreeNode> parent, bool isLeft);

    // Parcours en ordre pour afficher les valeurs
    void inorderTraversal(std::shared_ptr<TreeNode> node);
};



#endif