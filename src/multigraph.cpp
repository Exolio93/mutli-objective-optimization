#include "../include/multigraph.hpp"
#include "../include/tools.hpp"
#include <iostream>


void Arc::display(){
    std::cout<< n_from<<" " << n_to<< " : [ ";
    for (int i = 0; i < dim; ++i) {
        std::cout << weights[i] << " ";
    }
    std::cout <<"]"<< std::endl;
}


void Multigraph::addArc(int i, int j, std::vector<int> ws) {

    if (i>=N || i<0 ||j>=N || j<0 ) {
        print_and_exit("addEdge : La valeur des sommets n'est pas correcte");
    }
    if (static_cast<int>(ws.size()) != dim) {
        
        print_and_exit("addEdge : Le vecteur en entrée n'est pas de taille dim");
    }

    ////////////////////

    A_bool[i][j] = 1;
    A[i][j] = Arc(i,j,ws);
    

}

Multigraph Multigraph::generate_graph(int dim, int N, float rho, int val_max){
    
    Multigraph g = Multigraph(dim,N);

    std::random_device rd;  // Pour obtenir une graine aléatoire
    std::mt19937 gen(rd()); // Mersenne Twister pour générer des nombres pseudo-aléatoires
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> dis_int(0, val_max);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {

            if (dis(gen)<rho) {
                g.A_bool[i][j] = true;

                std::vector<int> ws(dim,0);
                for(int k =0;k<dim;++k){ws[k] = dis_int(gen);}
                g.addArc(i,j,ws);
            } 
            
        }
    }


    return g;
}