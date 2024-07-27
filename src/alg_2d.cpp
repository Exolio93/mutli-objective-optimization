#include "../include/alg_2d.hpp"
#include<chrono>
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;


void labels_update(std::vector<Label_set> &labels, Arc &Wij,Queue &queue){
    bool b = merger_pareto_set(labels, Wij);
    if(b){
        queue.add_point(Wij.n_to);
    }
    
}


void labels_update_using_AUC(std::vector<Label_set> &labels, Arc &Wij,Heap &queue,std::vector<std::vector<float>> &borders){
    bool b = merger_pareto_set(labels, Wij);
    if(b){
        queue.push(Heap_elt(Wij.n_to, labels[Wij.n_to], borders));
    }
    
}
 

bool merger_pareto_set(std::vector<Label_set> &labs,Arc &Wij){

    Label_set new_label_set = Label_set();
    bool add2queue = false;
    auto it_j= labs[Wij.n_to].set.begin(); //x,y
    auto it_i = labs[Wij.n_from].set.begin();// + Wij --> w,t

    /**********
     * --> 1st case : x <= w AND y <= t :
     * advance(w,t)
     * 
     * --> 2nd case : x < w AND y > t :
     * add(x,y), advance(x,y)
     *
     * --> 3rd case : x > w AND y < t :
     * add(w,t), advance(w,t)
     * 
     * --> 4th case : x >= w AND y >= t :
     * advance(x,y)
     * 
    */

    while(it_j!= labs[Wij.n_to].set.end() && it_i != labs[Wij.n_from].set.end()) {

        //Case 1 B
        if((*it_j).getX() <= (*it_i).getX()+ Wij.weights[0]
        && (*it_j).getY() <= (*it_i).getY()+ Wij.weights[1]) {
            
            it_i++;
        }
        //Case 2 D
        else if ((*it_j).getX() < (*it_i).getX()+ Wij.weights[0]
        && (*it_j).getY() > (*it_i).getY()+ Wij.weights[1]){
        
            new_label_set.add_point_at_end(*it_j);
            it_j++;
            
        }

        //Case3 A
        else if((*it_j).getX() > (*it_i).getX()+ Wij.weights[0]
        && (*it_j).getY() < (*it_i).getY()+ Wij.weights[1]){
    
            add2queue = true;
            new_label_set.add_point_at_end(    Label((*it_i).getX() + Wij.weights[0],(*it_i).getY() + Wij.weights[1],Wij.n_from, &(*it_i))   );
            it_i++;
        }

        //Case4 C
        else if((*it_j).getX() >= (*it_i).getX()+ Wij.weights[0]
        && (*it_j).getY() >= (*it_i).getY()+ Wij.weights[1]){

            it_j++;
        }
        else {
            std::cout<< "This message shouldn't be seen !"<<std::endl;
        }
    }


    if(it_j == labs[Wij.n_to].set.end() && it_i == labs[Wij.n_from].set.end()){
        return add2queue;
    }

    if(it_j == labs[Wij.n_to].set.end()) {
        
        if(new_label_set.set.empty()){
            while(it_i!=labs[Wij.n_from].set.end()) {
                
                new_label_set.add_point_at_end( Label((*it_i).getX() + Wij.weights[0],(*it_i).getY() + Wij.weights[1],Wij.n_from, &(*it_i)) );
                add2queue = true;
                it_i++;
                
            }
            labs[Wij.n_to] = new_label_set;
            return add2queue;
        }
        else {
            Label last = new_label_set.get_last();
            while(it_i!=labs[Wij.n_from].set.end()) {
                if (last.getY()>(*it_i).getY()) {
                    new_label_set.add_point_at_end(  Label((*it_i).getX() + Wij.weights[0],(*it_i).getY() + Wij.weights[1],Wij.n_from, &(*it_i))  );
                    add2queue = true;
                    
                }
                it_i++;
            }
            labs[Wij.n_to] = new_label_set;
            return add2queue;
        }
    }

    if(it_i == labs[Wij.n_from].set.end()) {
        if(new_label_set.set.empty()){
            return false;
        }
        else {
            Label last = new_label_set.get_last();
            while(it_j!=labs[Wij.n_to].set.end()) {
                if (last.getY()>(*it_j).getY()) {
                    new_label_set.add_point_at_end(*it_j);
    
                    
                }
                it_j++;
            }
            labs[Wij.n_to] = new_label_set;
            return add2queue;
        }
    }
    std::cout<< "This message shouldn't be seen"<<std::endl;
    return false;

}



std::vector<Label_set> shortest_path_2D(Graph g, int s, bool display) {
    
    


    float counter = 0;
    float counter2 = 0;
    float total_l =1;
    auto start = Clock::now();
    auto end = Clock::now();
    auto start1 = Clock::now();
    auto end1 = Clock::now();
    auto start2 = Clock::now();
    auto end2 = Clock::now();
    auto start3 = Clock::now();
    auto end3 = Clock::now();

    auto durations = std::vector<Duration>(5,Duration(0));

    int av_size = 0;

    start = Clock::now();

    if (g.dim !=2) {
        print_and_exit("dijkstra_bin : La dimension n'est pas de 2");
    }
    //Labels
    std::vector<Label_set> labels = std::vector<Label_set>(g.N, Label_set());
    labels[s].add_point(0,0,s,nullptr);

    //Queue
    Queue q = Queue(g.N);
    q.add_point(s);


    
    while(q.size() >0) {
        counter++;
        
        
        start1 = Clock::now();
        int pivot = q.pick();
        total_l += q.size();
        end1 = Clock::now();
        start2 = Clock::now();
        for (auto it = g.A[pivot].begin(); it != g.A[pivot].end();it++) {
            counter2++;
            start3 = Clock::now();
            labels_update(labels,(*it), q);
            end3 = Clock::now();
            durations[3] += end3-start3;
        
        }
        end2 = Clock::now();
        
        durations[1] += end1 - start1;
        durations[2] += end2 - start2;

    }
    end = Clock::now();
    durations[0] = end - start;

    /////////////////////////////////

    std::cout
    
    <<"\nTotal time: "<<durations[0].count()
    <<"\n\% for queue : "<<durations[1].count()/durations[0].count()
    << "\n\% for travel neighbors : "<<(durations[2].count()-durations[3].count())/durations[0].count()
    << "\n\% for update a labels : "<<durations[3].count()/durations[0].count()
    <<"\naverage size of queue : "<<total_l/counter
    <<"\niteration of while loop : "<<counter
    <<"\nAv size label_set :"<<av_size/(counter2*2)
    
    <<std::endl;

    if (display) {
        for(int i =0; i<g.N; ++i) {
            std::cout<<"|||||||||||||||||||"<<std::endl;
            std::cout<<"NODE "<<i<<std::endl;
            labels[i].print();
        }
    }

    // std::ofstream outFile("../save/test/solution");
    // outFile<<g.N<<std::endl;
    // for (int i = 0;i<g.N;i++) {
    //     for(auto it = labels[i].set.begin();it!=labels[i].set.end();++it) {
    //         outFile<<(*it).getX()<< " "<<(*it).getY()<<" "<<(*it).getPred()<<std::endl;
    //     }
    //     outFile<<"*"<<std::endl;
    // }
    return labels;
    
    
    
}

std::vector<Label_set> shortest_path_2D_using_AUC(Graph g, int s, bool display) {
    
    if (g.dim !=2) {
        print_and_exit("dijkstra_bin : La dimension n'est pas de 2");
    }
    
    


    float counter = 0;
    float total_l =1;
    
    auto start = Clock::now();
    auto end = Clock::now();
    auto start1 = Clock::now();
    auto end1 = Clock::now();
    auto start2 = Clock::now();
    auto end2 = Clock::now();
    auto start3 = Clock::now();
    auto end3 = Clock::now();

    float counter2 = 0;
    int av_size = 0;

    auto durations = std::vector<Duration>(5,Duration(0));

    start = Clock::now();


    //Labels
    std::vector<Label_set> labels = std::vector<Label_set>(g.N, Label_set());
    labels[s].add_point(0,0,s, nullptr);

    std::vector<std::vector<float>> borders = initialize_shape_pareto_set(g, s);

    //Queue 
    Heap q = Heap(g.N);
    q.push(Heap_elt(s, labels[s], borders));

    end = Clock::now();
    durations[4] = end - start;
    while(q.size() >0) {
        counter++;

        start1 = Clock::now();

        Heap_elt pivot = q.top();
        q.pop();

        total_l += q.size();
        end1 = Clock::now();
        start2 = Clock::now();
        for (auto it = g.A[pivot.n].begin(); it != g.A[pivot.n].end();it++) {
            counter2++;
            start3 = Clock::now();
            labels_update_using_AUC(labels,(*it), q, borders);
            end3 = Clock::now();
            durations[3] += end3-start3;
        }
        
        end2 = Clock::now();
        end = Clock::now();

        durations[1] += end1 - start1;
        durations[2] += end2 - start2;

    }
    end = Clock::now();
    durations[0] = end - start;


    std::cout
    
    <<"\nTotal time: "<<durations[0].count()
    <<"\nFirst DIjkstra : "<<durations[4].count()
    <<"\n\% for queue : "<<durations[1].count()/durations[0].count()
    << "\n\% for travel neighbors : "<<(durations[2].count()-durations[3].count())/durations[0].count()
    << "\n\% for update a labels : "<<durations[3].count()/durations[0].count()
    <<"\naverage size of queue : "<<total_l/counter
    <<"\niteration of while loop : "<<counter
    <<"\nAv size label_set :"<<av_size/(counter2*2)
    
    <<std::endl;

    return labels;
    
    
    
}



void print_path_from_solution(std::vector<Label_set> labels, int i){
    std::stack<int> nodes;

    for(auto it = labels[i].set.begin(); it != labels[i].set.end();++it) {
        std::cout<<"x : "<< (*it).getX() << ", y : "<<(*it).getY()<<std::endl;
        
        Label lab_pivot = (*it);

        nodes.push(i);

        while(true) {
            if(lab_pivot.getLabelPred()==nullptr) {
                break;
            }
            nodes.push(lab_pivot.getPred());
            lab_pivot = *lab_pivot.getLabelPred();        
        }
        while (!nodes.empty())
        {
        
            std::cout<<nodes.top()<<">";
            nodes.pop();
        }  
        std::cout<<std::endl; 


    }
}


std::vector<std::vector<float>> initialize_shape_pareto_set(Graph g, int s) {
    if (g.dim != 2) {
        print_and_exit("initialize_shape_pareto_set : dimension pas égale à 2");
    }

    std::vector<std::vector<float>> dists(4, std::vector<float>(g.N, std::numeric_limits<float>::max()));
    std::vector<std::list<int>> queues(2);
    std::vector<std::vector<int>> preds(2, std::vector<int>(g.N, -1));

    for (int i = 0; i < g.N; ++i) {
        queues[0].push_back(i);
        queues[1].push_back(i);
    }

    dists[0][s] = 0;dists[1][s] = 0;
    preds[0][s] = s;preds[1][s] = s;

    for (int count = 0; count < g.N; ++count) {
        
        //finding the index of the max:
        auto it_max1 = queues[0].begin();
        float val_max1 = std::numeric_limits<float>::max();
        auto it_max2 = queues[1].begin();
        float val_max2 = std::numeric_limits<float>::max();


        for(auto it = queues[0].begin(); it!=queues[0].end();++it){
            if(dists[0][*it]<= val_max1){
                it_max1 = it;
                val_max1 = dists[0][*it];
            }
        }
        for(auto it = queues[1].begin(); it!=queues[1].end();++it){
            if(dists[1][*it]<= val_max2){
                it_max2 = it;
                val_max2 = dists[1][*it];
            }
        }
        queues[0].erase(it_max1);
        queues[1].erase(it_max2);

        //neighboors processing :
        for (auto it = g.A[*it_max1].begin(); it != g.A[*it_max1].end();it++) {
            if (dists[0][(*it).n_to]>dists[0][*it_max1] +(*it).weights[0]){
                dists[0][(*it).n_to] = dists[0][*it_max1] +(*it).weights[0];
                preds[0][(*it).n_to] = *it_max1;
            }
        }
        for(auto it = g.A[*it_max2].begin(); it != g.A[*it_max2].end();it++) {
            if (dists[1][(*it).n_to]>dists[1][*it_max2] +(*it).weights[1]){
                dists[1][(*it).n_to] = dists[1][*it_max2] +(*it).weights[1];
                preds[1][(*it).n_to] = *it_max2;
            }
        }
    }
    int ind;
    float count;
    for(int i =0;i<g.N; ++i) {

        ind = i;
        count = 0;
        while(ind !=s) {

            count += g.getArc(preds[0][ind],ind).weights[1];
            ind = preds[0][ind];
        }
        dists[2][i] = count;

        ind = i;
        count = 0;
        while(ind!=s) {
            count += g.getArc(preds[1][ind],ind).weights[0];
            ind = preds[1][ind];
        }
        dists[3][i] = count;


    }

    return dists;

}