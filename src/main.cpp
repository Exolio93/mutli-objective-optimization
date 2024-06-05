#include <iostream>
#include<chrono>

#include "multigraph.hpp"
#include "alg_bin.hpp"

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

int main(){

    int state = 1;

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
        
        auto start = Clock::now();
        
        
        return 0;

    }
    


    return 0;
}



int main() {
    
}

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