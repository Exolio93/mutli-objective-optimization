#include "../include/alg_1d.hpp"

void dijkstra(const Graph& graph, int source) {
    std::vector<float> dist(graph.N, std::numeric_limits<float>::infinity());
    std::vector<int> prev(graph.N, -1);
    dist[source] = 0;

    using NodeDistPair = std::pair<float, int>;
    std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<NodeDistPair>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        float currentDist = pq.top().first;
        int i = pq.top().second;
        pq.pop();

        if (currentDist > dist[i]) continue;

        for (auto it = graph.A[i].begin(); it != graph.A[i].end(); ++it) {
    
            float weight = (*it).weights[0];
            float distanceThroughI = dist[i] + weight;

            if (distanceThroughI < dist[(*it).n_to]) {
                dist[(*it).n_to] = distanceThroughI;
                prev[(*it).n_to] = i;
                pq.push({distanceThroughI, (*it).n_to});
            }
        }
    }

    // Print results
    std::cout << "Node\tDistance from Source\tPath" << std::endl;
    for (int i = 0; i < graph.N; ++i) {
        std::cout << i << "\t" << dist[i] << "\t\t\t";
        int node = i;
        while (node != -1) {
            std::cout << node << " ";
            node = prev[node];
        }
        std::cout << std::endl;
    }
}

void bellmanFord(const Graph& graph, int source) {
    std::vector<float> dist(graph.N, std::numeric_limits<float>::infinity());
    std::vector<int> prev(graph.N, -1);
    dist[source] = 0;

    // Relax edges repeatedly
    for (int k = 0; k < graph.N - 1; ++k) {
        for (int i = 0; i < graph.N; ++i) {
            for (auto it = graph.A[i].begin(); it != graph.A[i].end(); ++it) {
                
                // Find the specific arc from i to j
                float weight = (*it).weights[0];
                if (dist[i] + weight < dist[(*it).n_to]) {
                    dist[(*it).n_to] = dist[i] + weight;
                    prev[(*it).n_to] = i;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < graph.N; ++i) {
        for (auto it = graph.A[i].begin(); it != graph.A[i].end(); ++it) {
           
            float weight = (*it).weights[0];
            if (dist[i] + weight < dist[(*it).n_to]) {
                std::cerr << "Graph contains a negative-weight cycle" << std::endl;
                return;
            }
        
        }
    }

    // Print results
    std::cout << "Node\tDistance from Source\tPath" << std::endl;
    for (int i = 0; i < graph.N; ++i) {
        std::cout << i << "\t" << dist[i] << "\t\t\t";
        int node = i;
        while (node != -1) {
            std::cout << node << " ";
            node = prev[node];
        }
        std::cout << std::endl;
    }
}