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

Multigraph Multigraph::generate_graph(int N, int dim, float rho, int val_max){
    
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


Multigraph Multigraph::load_graph(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        print_and_exit("load_graph : can't open the file");
    }
    std::string line;

    int N,dim;
    
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        iss>>N;
    }
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        iss>>dim;
    }


    Multigraph g = Multigraph(dim, N);


    int i,j;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> ws;
        int number;
        iss>>i>>j;
        while (iss >> number) {
            ws.push_back(number);
        }

        g.addArc(i,j,ws);
    }

    return g;


    

};

void Multigraph::save_graph(std::string path){
    std::ofstream outFile(path);
    outFile<<N<<std::endl;
    outFile<<dim<<std::endl;
    for(int i = 0;i<N;++i) {
        for(int j = 0;j<N;++j) {
            if (A_bool[i][j] == 1) {
                outFile<<i<<" "<<j;
                for(int k = 0;k<A[i][j].weights.size();k++){
                    outFile<<" "<<A[i][j].weights[k];
                }
                outFile<<std::endl;
            }
        }
    }
};