#ifndef MULTIGRAPH_HPP
#define MULTIGRAPH_HPP

#include <vector>
#include <list>
#include <random>
#include <fstream>
#include <string>
#include <sstream>

// Les sommets sont des entier allant de 0 à m-1

class Arc {
public :
    int n_from;
    int n_to;
    int dim;
    std::vector<int> weights;
    
    Arc(){};

    Arc(int from, int to, std::vector<int> ws){
        n_from = from;
        n_to = to;
        dim = ws.size();
        weights = ws;};

    void display();

};

class Multigraph {
public :
    int dim;
    int N;
    std::vector<std::vector<Arc>> A;
    std::vector<std::vector<bool>> A_bool;


    Multigraph(int dim_size, int N_size) {
        dim = dim_size;
        N = N_size;
        A.resize(N);
        A_bool.resize(N);
        for (int i = 0; i < N; ++i) {
            A_bool[i] = std::vector<bool>(N, 0);
            A[i] = std::vector<Arc>(N, Arc());
        
        }
    };

    void print();
    void addArc(int i, int j, std::vector<int> ws);



    //rho : proportion d'arc
    //val_max : max value for each component of arcs
    static Multigraph generate_graph(int dim, int N, float rho, int val_max);

    static Multigraph load_graph(std::string path);
    void save_graph(std::string path);

};


class Multigraph2 {
public :
    int dim;
    int N;
    std::vector<std::vector<Arc>> A;


    Multigraph2(int dim_size, int N_size) {
        dim = dim_size;
        N = N_size;
        A.resize(N);
    };

    void print();

    void addArc(int i, int j, std::vector<int> ws);

    //rho : density
    //val_max : max value for each component of arcs

    static Multigraph2 load_graph(std::string path);
};


#endif