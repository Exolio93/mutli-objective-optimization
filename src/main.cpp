#include <iostream>
#include<chrono>
#include<string>
#include "graph.hpp"

#include "data_struct_2d.hpp"
#include "alg_2d.hpp"
#include "alg_1d.hpp"

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

void calculate(int n, int number_of_graph, float density) {
    std::vector<Graph> graphs;

    // Ajout des graphes au vecteur
    for (int i = 0; i < number_of_graph; ++i) {
        graphs.push_back(Graph::generate_graph_on_grid(n, 2, density, 100));
    }

    
    std::vector<double> av_result(7,0);
    std::vector<double> result;
    for (int i = 0; i < number_of_graph; ++i) {
        result = shortest_path_NP_FIFO(graphs[i], 0, false);
        for(int k =0; k<av_result.size();++k){
            av_result[k] += result[k];
        }
        
    }
    std::cout<<av_result[0]/number_of_graph<<std::endl;
    std::cout<<av_result[2]/number_of_graph<<std::endl;
    std::cout<<av_result[3]/number_of_graph<<std::endl;
    std::cout<<av_result[4]/number_of_graph<<std::endl;
    std::cout<<av_result[5]/number_of_graph<<std::endl;
    std::cout<<av_result[6]/number_of_graph<<std::endl;

}


int main(int argc, char* argv[]){

    int state =-1;


    if (state == 0) {
        // Graph g = Graph::load_graph("../save/temp/small_graph");
        
        // std::vector<Label_set> labs = shortest_path_2D(g,0,false);
        // print_path_from_solution(labs, 3);

        // return 0;

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
        std::string d5000 = "../save/temp/2_5000_10";


        Graph g2 = Graph::load_graph(d1000);
        Graph g4 = Graph::load_graph(d2000);
        Graph g6 = Graph::load_graph(d3000);
        Graph g8 = Graph::load_graph(d4000);
        Graph g9 = Graph::load_graph(d5000);

        


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
        calculate(std::atoi(argv[1]), std::atoi(argv[2]), std::atof(argv[3]));
    
    }

    if (state == -1) {
        std::cout << "What would you like to do:\n";
        std::cout << "- Solve on a new graph (1)\n";
        std::cout << "- Solve on an existing graph (2)\n";
        std::cout << "- Save a new graph (3)\n";
        

        int choice;
        std::cout << "Please enter your choice (1/2/3): ";
        std::cin >> choice;

        if(choice < 1 || choice > 3) {
            std::cerr << "Invalid choice. Please restart the program and enter a valid option." << std::endl;
            return 1; 
        }
        
        if (choice == 2)
        {
            std::string name;
            int n;
            float density;

            std::cin.ignore();
            std::cout << "\nFile name: (ex : temp/2_50_10): ";
            std::getline(std::cin, name);


            std::cout << "\nChoice of algorithm\n";
            std::cout << "- Node processing - FIFO (1)\n";
            std::cout << "- Node processing - Hyper-volume (2)\n";
            std::cout << "- Label processing - FIFO (3)\n";
            std::cout << "- Label processing - Tree (4)\n";
            std::cin>>n;

            Graph g = Graph::load_graph("../save/" + name);

            int choice2;
            std::cout << "Please enter your choice (1/2/3/4): ";
            std::cin >> choice2;
            if(choice2 < 1 || choice2 > 3) {
                std::cerr << "Invalid choice. Please restart the program and enter a valid option." << std::endl;
                return 1; 
            }

            if (choice2 == 1) {
                shortest_path_NP_FIFO(g,0,false);
                return 0;
            }
            if (choice2 == 2) {
                shortest_path_NP_HP(g,0,false);
                return 0;
            }
            if (choice2 == 3) {
                shortest_path_LP_FIFO(g,0,false);
                return 0;
            }
            if (choice2 == 4) {
                shortest_path_LP_TREE(g,0,false);
                return 0;
            }

            


        }

        if (choice == 3)
        {
            std::string name;
            int n;
            float density;

            std::cin.ignore();
            std::cout << "\nFile name: ";
            std::getline(std::cin, name);


            std::cout << "\nNumber of nodes: ";
            std::cin>>n;
            if(n <= 0) {
                std::cerr << "Invalid choice. Please restart the program and enter a valid option." << std::endl;
                return 1; 
            }


            std::cout << "\nDensity: ";
            std::cin>>density;
            if(density < 0 || density > 1) {
                std::cerr << "Invalid choice. The density must be between 0 and 1. Please restart the program and enter a valid option." << std::endl;
                return 1; 
            }

            Graph::generate_graph_on_grid(n,2,density,100).save_graph("../save/set/" + name);

        }
        






       

    }



    return 0;
}

