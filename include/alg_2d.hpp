#ifndef ALG_2D_HPP
#define ALG_2D_HPP

#include "graph.hpp"
#include "tools.hpp"
#include "data_struct_2d.hpp"
#include<queue>
#include<tuple>
#include <algorithm> 
#include<vector>

std::vector<std::vector<float>> initialize_shape_pareto_set(Graph g, int s);
void shortest_path_2D(Graph g, int s, bool display);
void shortest_path_2D_using_AUC(Graph g, int s, bool display);

void labels_update(std::vector<Label_set> &labels, Arc &Wij,std::vector<int> &queue);
void labels_update_using_AUC(std::vector<Label_set> &labels, Arc &Wij,Heap &queue, std::vector<std::vector<int>> &borders);

bool merger_pareto_set(std::vector<Label_set> &labs, Arc &Wij);





#endif