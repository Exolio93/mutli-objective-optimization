#include <iostream>
#include<chrono>
#include <filesystem>

#include "multigraph.hpp"
#include "alg_bin.hpp"


int main(){
    int num = 20;
    auto start = std::chrono::high_resolution_clock::now();
    
    for(int k = 0;k<num;++k) {
        
        Multigraph g = Multigraph::load_graph("../save/dataset1/graph" + std::to_string(k));
        dijkstra_bin(g, 0, 0, false);
        std::cout<<"ok"<<std::endl;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    

    auto start2 = std::chrono::high_resolution_clock::now();
    std::cout<<"----"<<std::endl;
    for(int k = 0;k<num;++k) {
        
        Multigraph g = Multigraph::load_graph("../save/dataset1/graph" + std::to_string(k));
        dijkstra_bin(g, 0, 1,false);
        std::cout<<"ok"<<std::endl;
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    
    Multigraph g = Multigraph(2, 4);

    g.addArc(0,1,{4,1});
    g.addArc(0,2,{3,5});
    g.addArc(1,3,{6,4});
    g.addArc(1,2,{2,2});
    g.addArc(2,3,{1,2});

    dijkstra_bin(g, 0,1, true);


    
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Temps d'exécution pour random : " << duration.count() << " ms" << std::endl;
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;
    std::cout << "Temps d'exécution pour lexicographic : " << duration2.count() << " ms" << std::endl;


    return 0;
}



/*
int main(){
    
    Multigraph g = Multigraph(2, 4);

    g.addArc(0,1,{4,1});
    g.addArc(0,2,{3,5});
    g.addArc(1,3,{6,4});
    g.addArc(1,2,{2,2});
    g.addArc(2,3,{1,2});

    dijkstra_bin(g, 0,1);


    return 0;
}
*/


/*
//Génération et sauvegarde de graphs
int main(){
    int num = 20;
    std::vector<Multigraph> l;


    for(int k = 0; k<num; ++k) {
        Multigraph::generate_graph(2,50,0.5,20).save_graph("../save/dataset1/graph" + std::to_string(k));

    }
    return 0;
}*/