#include <iostream>
#include<chrono>

#include "graph.hpp"
#include "data_struct_2d.hpp"
#include "alg_2d.hpp"
#include "alg_1d.hpp"

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

int main(int argc, char* argv[]){

    if (argc != 5) {
        int state =0;


        if (state == 0) {
            Graph g = Graph::load_graph("../save/temp/small_graph");
            
            std::vector<Label_set> labs = shortest_path_2D(g,0,false);
            print_path_from_solution(labs, 3);

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
            Graph g = Graph::load_graph("../save/graph_to_plot/2_20_50");

            auto lab1 = shortest_path_2D(g, 0, false);
            auto lab2 = shortest_path_2D_using_AUC(g,0,false);


            for(auto it = lab1.begin(); it !=lab1.end(); ++it) {
                std::cout<<(*it).set.size()<<std::endl;
            }
            
            std::cout<<"\n\nFIFO : "<<std::endl;
            print_path_from_solution(lab1,19);

            std::cout<<"\n\nHyper volume"<<std::endl;
            print_path_from_solution(lab2,19);

        }

        if (state == 3) {
            Graph::generate_graph_on_grid(1000, 2, 0.7, 100).save_graph("../save/dataset_2/2_1000_70");
            Graph::generate_graph_on_grid(2000, 2, 0.7, 100).save_graph("../save/dataset_2/2_2000_70");
            Graph::generate_graph_on_grid(2000, 2, 0.5, 100).save_graph("../save/dataset_2/2_2000_50");
        }
    }

    else {
        Graph g = Graph::load_graph(argv[1]);
        std::vector<Label_set> labs;
        int alg = std::atoi(argv[2]);
        int s = std::atoi(argv[3]);
        int t = std::atoi(argv[4]);

        if (t>= g.N || t<0) {
            std::cerr << "The objective node does not belong to the graph"<< std::endl;
        }

        if (s>= g.N || s<0) {
            std::cerr << "The source node does not belong to the graph"<< std::endl;
        }
        
        if (alg !=0 && alg!=1) {
            std::cerr << "The argument for algorithm must be equal to 0 or 1"<< std::endl;
        }

        std::cout<< "---------- " <<std::endl;
        if (alg == 0) {
            
            auto start = Clock::now();
            labs = shortest_path_2D(g, s, false);
            auto end = Clock::now();
            Duration d = end - start;
            std::cout<< "Total time : " << d.count()<<std::endl;

        }
        if (alg == 1) {
            auto start = Clock::now();
            labs = shortest_path_2D_using_AUC(g, s, false);
            auto end = Clock::now();
            Duration d = end - start;
            std::cout<< "Total time : " << d.count()<<std::endl;
        }

        std::cout<< "---------- \n" <<std::endl;

        print_path_from_solution(labs, t);

        
    
    }
    


    return 0;
}

