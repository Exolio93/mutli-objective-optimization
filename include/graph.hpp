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
    std::vector<std::list<Arc>> A;

    Graph(int dim_size, int N_size) 
        : dim(dim_size), N(N_size), A(N_size) {
        // Vous pouvez ajouter d'autres initialisations ici si nécessaire
    }

    void addArc(int i, int j, std::vector<float> ws);
    Arc getArc(int i, int j);
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