#include <iostream>
#include<chrono>

#include "multigraph.hpp"
#include "alg_bin.hpp"

int main(){
    
    Multigraph g = Multigraph(2, 4);

    g.addArc(0,1,{4,1});
    g.addArc(0,2,{3,5});
    g.addArc(1,3,{6,4});
    g.addArc(1,2,{2,2});
    g.addArc(2,3,{1,2});

    dijkstra_bin(g, 0,0);


    return 0;
}


/*
int main() {
    int num = 50;
    std::vector<Multigraph> l(num,Multigraph::generate_graph(2,100,0.5,20));
    
    auto start = std::chrono::high_resolution_clock::now();
    for(int k = 0;k<num;++k) {
        Multigraph g = Multigraph::generate_graph(2,100,0.5,10);
        dijkstra_bin(l[k],0, 0);
        std::cout<<"ok"<<std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Temps d'exécution pour random : " << duration.count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for(int k = 0;k<num;++k) {
        Multigraph g = Multigraph::generate_graph(2,100,0.5,10);
        dijkstra_bin(l[k],0, 1);
        std::cout<<"ok"<<std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Temps d'exécution pour max_it : " << duration.count() << " ms" << std::endl;    
    
    return 0;
}*/

/*
int main(){
    Queue q = Queue();
    q.add_point(0);
    q.add_point(1);
    q.add_point(2);
    q.add_point(3);
    q.add_point(4);
    q.add_point(5);
    q.print();
    std::cout<<q.random_choice()<<std::endl;
    q.print();
    
    return 0;
}
*/