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
        int state =2;


        if (state == 0) {
            Graph g = Graph::load_graph("../save/temp/small_graph");
            
            std::vector<Label_set> labs = shortest_path_2D(g,0,false);
            print_path_from_solution(labs, 3);

            return 0;

        }
        if (state == 1) {

            std::string d500 = "../save/temp/2_500_10";
            std::string d1000 = "../save/temp/2_1000_10";
            std::string d1500 = "../save/temp/2_1500_10";
            std::string d2500 = "../save/temp/2_2500_10";
            std::string d3500 = "../save/temp/2_3500_10";
            std::string d2000 = "../save/temp/2_2000_10";
            std::string d3000 = "../save/temp/2_3000_10";
            std::string d4000 = "../save/temp/2_4000_10";


            Graph g1 = Graph::load_graph(d500);
            Graph g2 = Graph::load_graph(d1000);
            Graph g3 = Graph::load_graph(d1500);
            Graph g4 = Graph::load_graph(d2000);
            Graph g5 = Graph::load_graph(d2500);
            Graph g6 = Graph::load_graph(d3000);
            Graph g7 = Graph::load_graph(d3500);
            Graph g8 = Graph::load_graph(d4000);

            
            shortest_path_2D(g1,0,false);
            shortest_path_2D(g2,0,false);
            shortest_path_2D(g3,0,false);
            shortest_path_2D(g4,0,false);
            shortest_path_2D(g5,0,false);
            shortest_path_2D(g6,0,false);
            shortest_path_2D(g7,0,false);
            shortest_path_2D(g8,0,false);

            std::cout<<"-----------"<<std::endl;

            shortest_path_2D_using_AUC(g1,0,false);
            shortest_path_2D_using_AUC(g2,0,false);
            shortest_path_2D_using_AUC(g3,0,false);
            shortest_path_2D_using_AUC(g4,0,false);
            shortest_path_2D_using_AUC(g5,0,false);
            shortest_path_2D_using_AUC(g6,0,false);
            shortest_path_2D_using_AUC(g7,0,false);
            shortest_path_2D_using_AUC(g8,0,false);


            return 0;

        }
        if (state == 2) {
            TreeNode* root = new TreeNode(2, 1, 6, 5);

            // Création des nœuds enfants
            root->left = new TreeNode(2, 3, 3, 5);
            root->right = new TreeNode(4, 1, 6, 2);

            // Création des feuilles avec des labels
            root->left->left = new TreeNode(new Label(2, 5, 0, nullptr));
            root->left->right = new TreeNode(new Label(3, 3, 0, nullptr));
            root->right->left = new TreeNode(new Label(4, 2, 0, nullptr));
            root->right->right = new TreeNode(new Label(6, 1, 0, nullptr));

            root->print();
            Label l = Label(2.5,4,0,nullptr);
            root->insert_label(&l);  
            std::cout<<"--------"<<std::endl;

            // auto new_node = std::make_shared<TreeNode>(Label(-1,-1,0,nullptr));
            // root->right = new_node;
            root->print();

    


        }

        if (state == 3) {
            Graph::generate_graph_on_grid(1500, 2, 0.1, 100).save_graph("../save/temp/2_1500_10");
            Graph::generate_graph_on_grid(2500, 2, 0.1, 100).save_graph("../save/temp/2_2500_10");
            Graph::generate_graph_on_grid(3500, 2, 0.1, 100).save_graph("../save/temp/2_3500_10");
           

        
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

