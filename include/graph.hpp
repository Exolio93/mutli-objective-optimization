#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>
#include <random>
#include <fstream>
#include <string>
#include <sstream>


class Arc {
public :
    int n_from;
    int n_to;
    int dim;
    std::vector<float> weights;
    
    Arc(){};

    Arc(int from, int to, std::vector<float> ws){
        n_from = from;
        n_to = to;
        dim = ws.size();
        weights = ws;
        };

    void display();

};

class Graph {
public :
    int dim;
    int N;
    std::vector<std::vector<Arc>> A;
    std::vector<std::vector<bool>> A_bool;


    Graph(int dim_size, int N_size) {
        dim = dim_size;
        N = N_size;
        A.resize(N);
        A_bool.resize(N);
        for (int i = 0; i < N; ++i) {
            A_bool[i] = std::vector<bool>(N, 0);
            A[i] = std::vector<Arc>(N, Arc());
        
        }
    };

    void addArc(int i, int j, std::vector<float> ws);

    //rho : arc rate
    //val_max : max value for each component of arcs

    //First alg for generating a graph : random weights
    static Graph generate_graph_randomly(int N, int dim, float rho, float val_max);

    //Second alg for generating a graph : euclidean distance & another distance 
    static Graph generate_graph_on_grid(int N, int dim, float rho, float val_max);
    
    static Graph load_graph(std::string path);
    void save_graph(std::string path);
    

};


#endif