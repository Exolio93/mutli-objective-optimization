#include <iostream>
#include<chrono>

#include "multigraph.hpp"
#include "alg_bin.hpp"

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

int main(){

    int state =1;

    if (state == 0) {
        Multigraph g = Multigraph(2, 4);

        g.addArc(0,1,{4,1});
        g.addArc(0,2,{3,5});
        g.addArc(1,3,{6,4});    
        g.addArc(1,2,{2,2});
        g.addArc(2,3,{1,2});

        dijkstra_bin(g, 0,0, true);
        return 0;

    }
    if (state == 1) {
        std::string d500 = "../save/temp/2_500_10";
        std::string d1000 = "../save/temp/2_1000_10";
        std::string d2000 = "../save/temp/2_2000_10";
        std::string d4000 = "../save/temp/2_4000_10";

        Multigraph g1000 = Multigraph::load_graph(d1000);


        auto start = Clock::now();
        dijkstra_bin(g1000,0,0,false);
        auto end = Clock::now();

        Duration d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;   

        
        return 0;

    }
    if (state == 2) {
        Multigraph::generate_graph(4000,2,0.1,20).save_graph("../save/temp/2_4000_10");

    }
    


    return 0;
}

