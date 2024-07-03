#include "../include/graph.hpp"
#include "../include/tools.hpp"
#include <iostream>


void Arc::display(){
    std::cout<< n_from<<" " << n_to<< " : [ ";
    for (int i = 0; i < dim; ++i) {
        std::cout << weights[i] << " ";
    }
    std::cout <<"]"<< std::endl;
}




void Graph::addArc(int i, int j, std::vector<float> ws) {

    if (i>=N || i<0 ||j>=N || j<0 ) {
        print_and_exit("addEdge : La valeur des sommets n'est pas correcte");
    }
    if (static_cast<float>(ws.size()) != dim) {
        
        print_and_exit("addEdge : Le vecteur en entrée n'est pas de taille dim");
    }
    A[i].push_back(Arc(i,j,ws));

}




Graph Graph::generate_graph_randomly(int N, int dim, float rho, float val_max){
    
    Graph g = Graph(dim,N);

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_real_distribution<> dis_int(0, val_max);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {

            if (dis(gen)<rho) {

                std::vector<float> ws(dim,0);
                for(int k =0;k<dim;++k){ws[k] = dis_int(gen);}
                g.addArc(i,j,ws);
            } 
            
        }
    }
    return g;
}




Graph Graph::generate_graph_on_grid(int N, int dim, float rho, float val_max){
    
    Graph g = Graph(dim,N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_real_distribution<> dis_int(0, val_max);

    std::vector<std::vector<float>> v(2, std::vector<float>(N,0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
            v[i][j] = dis_int(gen);
            
        }
    }
    std::vector<std::vector<float>> attractive_points(2, std::vector<float>(dim-1,0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < dim-1; ++j) {
            attractive_points[i][j] = dis_int(gen);
            
        }
    }

    v[0][0] = 0;
    v[1][0] = 0;
    v[0][N-1] = val_max;
    v[1][N-1] = val_max;

    std::ofstream outFile("../save/test/map");
    outFile<<N<<std::endl;
    outFile<<val_max<<std::endl;

    for(int j = 0;j<N;++j) {
        outFile<<j<<" "<<v[0][j]<< " "<<v[1][j];
        outFile<<std::endl;
    }

    for(int j = 0;j<dim-1;++j) {
        outFile<<j<<" "<<attractive_points[0][j]<< " "<<attractive_points[1][j];
        outFile<<std::endl;
    }


    
    //adding weights
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {

            if (dis(gen)<rho and i!=j) {
                std::vector<float> ws(dim,0);
                //hypothèse ou dim est égal à 2 :
                ws[0] = std::sqrt((v[0][i] - v[0][j])*(v[0][i] - v[0][j]) + (v[1][i] - v[1][j])*(v[1][i] - v[1][j]));
                for(int k = 0; k<dim-1;++k) {
                    float d1 = std::sqrt((v[0][i] - attractive_points[0][k])*(v[0][i] - attractive_points[0][k]) 
                    + (v[1][i] - attractive_points[1][k])*(v[1][i] - attractive_points[1][k]));
                    float d2 = std::sqrt((v[0][j] - attractive_points[0][k])*(v[0][j] - attractive_points[0][k]) 
                    + (v[1][j] - attractive_points[1][k])*(v[1][j] - attractive_points[1][k]));
                    ws[k+1] = (d1 + d2)/2;

                }

                g.addArc(i,j,ws);
            } 
            
        }
    }


    return g;
}




Graph Graph::load_graph(std::string path) {
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

    Graph g = Graph(dim, N);
    int i,j;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<float> ws;
        float number;
        iss>>i>>j;
        while (iss >> number) {
            ws.push_back(number);
        }
        g.addArc(i,j,ws);
    }

    return g;


    

};

Arc Graph::getArc(int i, int j) {
    for (auto it = A[i].begin(); it != A[i].end(); ++it) {
        if ((*it).n_to == j) {
            return *it;
        }
    }
    print_and_exit("Error in getArc : Arc doesn't exist");
    return Arc();
}



void Graph::save_graph(std::string path){
    std::ofstream outFile(path);
    outFile<<N<<std::endl;
    outFile<<dim<<std::endl;
    for(int i = 0;i<N;++i) {
        
        for(auto it = A[i].begin(); it !=A[i].end(); ++it) {
            outFile<<i<<" "<<(*it).n_to;
            for(int k = 0;k<(*it).weights.size();k++){
                outFile<<" "<<(*it).weights[k];
            }
            outFile<<std::endl;
        }
    }
};