#ifndef ALG_1D_HPP
#define ALG_1D_HPP

#include "graph.hpp"
#include "tools.hpp"
#include<queue>
#include<vector>
#include <limits>

void dijkstra(const Graph& graph, int source);
void bellmanFord(const Graph& graph, int source);

#endif