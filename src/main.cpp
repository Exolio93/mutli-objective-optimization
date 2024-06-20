#include <iostream>
#include<chrono>

#include "graph.hpp"
#include "alg_bin.hpp"

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

int main(){
    std::cout << "__cplusplus value: " << __cplusplus << std::endl;

    int state =1;


    if (state == 0) {
        Graph g = Graph(2, 4);

        g.addArc(0,1,{4,1});
        g.addArc(0,2,{3,5});
        g.addArc(1,3,{6,4});    
        g.addArc(1,2,{2,2});
        g.addArc(2,3,{1.1,2.1});

        shortest_path_2D(g,0,true);
        return 0;

    }
    if (state == 1) {
        std::string d200_10 = "../save/dataset_2/2_200_10";
        std::string d200_30 = "../save/temp/2_200_30";
        std::string d200_50 = "../save/temp/2_200_50";
        std::string d200_70 = "../save/temp/2_200_70";
        std::string d500 = "../save/dataset_2/2_500_10";
        std::string d1000 = "../save/dataset_2/2_1000_10";
        std::string d2000 = "../save/dataset_2/2_2000_10";
        std::string d4000 = "../save/temp/2_4000_10";

        Graph g1 = Graph::load_graph(d200_10);
        Graph g2 = Graph::load_graph(d500);
        Graph g3 = Graph::load_graph(d1000);


        auto start = Clock::now();
        shortest_path_2D(g1,0,false);
        auto end = Clock::now();
        Duration d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;

        start = Clock::now();
        shortest_path_2D(g2,0,false);
        end = Clock::now();
        d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;

        start = Clock::now();
        shortest_path_2D(g3,0,false);
        end = Clock::now();
        d = end - start;
        std::cout<< "Total time : " << d.count()<<std::endl;

        return 0;

    }
    if (state == 2) {
        Graph::generate_graph_randomly(200,2,0.3,20).save_graph("../save/temp/2_200_30");
        Graph::generate_graph_randomly(200,2,0.5,20).save_graph("../save/temp/2_200_50");
        Graph::generate_graph_randomly(200,2,0.7,20).save_graph("../save/temp/2_200_70");

    }
    if (state == 3) {
        Label_set l = Label_set();
        l.add_point(2,4,0);
        std::vector<std::vector<float>> v = {{1},{1},{6},{6}};
        std::cout<<l.calculate_AUC(v,0)<<std::endl;

    }
    if (state == 4) {
        Graph::generate_graph_on_grid(200, 2, 0.1, 100).save_graph("../save/dataset_2/2_200_10");
        Graph::generate_graph_on_grid(500, 2, 0.1, 100).save_graph("../save/dataset_2/2_500_10");
        Graph::generate_graph_on_grid(1000, 2, 0.1, 100).save_graph("../save/dataset_2/2_1000_10");
        Graph::generate_graph_on_grid(2000, 2, 0.1, 100).save_graph("../save/dataset_2/2_2000_10");
    }
    


    return 0;
}

