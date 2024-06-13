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

        dijkstra_bin(g,0,1,true);
        return 0;

    }
    if (state == 1) {
        std::string d200_10 = "../save/temp/2_200_10";
        std::string d200_30 = "../save/temp/2_200_30";
        std::string d200_50 = "../save/temp/2_200_50";
        std::string d200_70 = "../save/temp/2_200_70";
        std::string d500 = "../save/temp/2_500_10";
        std::string d1000 = "../save/temp/2_1000_10";
        std::string d2000 = "../save/temp/2_2000_10";
        std::string d4000 = "../save/temp/2_4000_10";

        Multigraph g_10 = Multigraph::load_graph(d1000);
        Multigraph g_30 = Multigraph::load_graph(d200_30);
        Multigraph g_50 = Multigraph::load_graph(d200_50);
        Multigraph g_70 = Multigraph::load_graph(d200_70);


        auto start = Clock::now();
        dijkstra_bin(g_10,0,0,false);
        auto end = Clock::now();

        Duration d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;
        std::cout<<"----------"<<std::endl;
        start = Clock::now();
        dijkstra_bin(g_10,0,1,false);
        end = Clock::now();

        d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;    
        // dijkstra_bin(g_30,0,0,false);
        // dijkstra_bin(g_50,0,0,false);
        // dijkstra_bin(g_70,0,0,false);
        // dijkstra_AUC(g_10,1,false);
        // dijkstra_AUC(g_30,1,false);
        // dijkstra_AUC(g_50,1,false);
        // dijkstra_AUC(g_70,1,false);
         

        
        return 0;

    }
    if (state == 2) {
        Multigraph::generate_graph(200,2,0.3,20).save_graph("../save/temp/2_200_30");
        Multigraph::generate_graph(200,2,0.5,20).save_graph("../save/temp/2_200_50");
        Multigraph::generate_graph(200,2,0.7,20).save_graph("../save/temp/2_200_70");

    }
    if (state == 3) {
        Label_set l = Label_set();
        l.add_point(3,4,0);
        l.add_point(4,3,0);
        std::vector<std::vector<int>> v = {{1},{1},{4},{4}};
        std::cout<<l.calculate_AUC(v,0)<<std::endl;



    }
    


    return 0;
}

