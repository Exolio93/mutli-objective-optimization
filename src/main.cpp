#include <iostream>
#include<chrono>
#include <filesystem>

#include "multigraph.hpp"
#include "alg_bin.hpp"



int main(){
    int state = 0;

    // some tests
    if (state == 0){
        int num = 20;
        std::string dataset = "../save/dataset_2_50_80p/graph";


        auto start = std::chrono::high_resolution_clock::now(); 
        for(int k = 0;k<1;++k) {
            Multigraph g = Multigraph::load_graph(dataset + std::to_string(k));
            std::cout<<"ok"<<std::endl;
        }
        auto end = std::chrono::high_resolution_clock::now();
        

        std::cout<<"----"<<std::endl;


        auto start2 = std::chrono::high_resolution_clock::now();
        for(int k = 0;k<1;++k) {
            Multigraph2 g = Multigraph2::load_graph(dataset + std::to_string(k));
            std::cout<<"ok"<<std::endl;
        }
        auto end2 = std::chrono::high_resolution_clock::now();
        


        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Temps d'exécution pour random : " << duration.count() << " ms" << std::endl;
        std::chrono::duration<double, std::milli> duration2 = end2 - start2;
        std::cout << "Temps d'exécution pour lexicographic : " << duration2.count() << " ms" << std::endl;


        return 0;
    }

    



    //////////////////////////////////////////////////////////////
    //create a dataset
    if(state == 1){
        int num = 20;
        std::vector<Multigraph> l;
        for(int k = 0; k<num; ++k) {
            Multigraph::generate_graph(2,50,0.8,20).save_graph("../save/dataset_2_50_80p/graph" + std::to_string(k));

        }
        return 0;
    }




    //////////////////////////////////////////////////////////////
    //basic graph + its solution
    if(state ==2) {
        Multigraph g = Multigraph(2, 4);

        g.addArc(0,1,{4,1});
        g.addArc(0,2,{3,5});
        g.addArc(1,3,{6,4});
        g.addArc(1,2,{2,2});
        g.addArc(2,3,{1,2});

        dijkstra_bin(g, 0,1, true);

        Multigraph2 g2 = Multigraph2::load_graph("../save/dataset1/graph"+ std::to_string(0));
        
        


    return 0;
    }

}

