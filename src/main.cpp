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
        std::string dataset = "../save/temp/2_500_10";
        Multigraph g = Multigraph::load_graph(dataset);

        auto start = Clock::now();
        dijkstra_bin(g,0,0,false);
        auto end = Clock::now();

        Duration d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;   
        
        return 0;

    }
    


    return 0;
}

