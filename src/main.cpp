#include <iostream>
#include<chrono>
#include <filesystem>

#include "multigraph.hpp"
#include "alg_bin.hpp"



int main(){
    int state = 0;

    // some tests
    if (state == 0){
        std::string dataset = "../save/temp/2_50_10";
        Multigraph g = Multigraph::load_graph(dataset);

        dijkstra_bin(g,0,1,0);
        

        return 0;
    }

    



    //////////////////////////////////////////////////////////////
    //create a dataset
    if(state == 1){
        int num = 1;
        std::vector<Multigraph> l;
        for(int k = 0; k<num; ++k) {
            Multigraph::generate_graph(2,500,0.1,20).save_graph("../save/temp/2_500_10");

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

