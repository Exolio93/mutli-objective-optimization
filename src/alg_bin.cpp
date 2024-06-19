#include "../include/alg_bin.hpp"
#include<chrono>
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

float Label::getX() const{
    return x;
}
float Label::getY() const{
    return y;
}
int Label::getPred() const{
    return pred;
}

void Label_set::print(){
    std::cout<<"-----"<<std::endl;
    for(auto it = set.begin();it!=set.end();++it) {
        std::cout<<"x:"<<(*it).getX()<< " y:"<<(*it).getY()<<" pred:"<<(*it).getPred()<<std::endl;
    }
    std::cout<<"-----"<<std::endl;

}



void labels_update(std::vector<Label_set> &labels,Arc &Wij,Queue &queue){
    bool b = false;
    int i = Wij.n_from;
    int j = Wij.n_to;
    auto it = labels[i].set.begin();
    for(int k=0; k<labels[i].set.size(); ++k) {
        float wx = (*it).getX();
        float wy = (*it).getY();
        b = labels[j].add_point(wx + Wij.weights[0], wy + Wij.weights[1], i)|| b;
        ++it;
    }
    if(b) {
        queue.add_point(j);
    }
    
}

void labels_update2(std::vector<Label_set> &labels, Arc &Wij,Queue &queue){
    bool b = add_pareto_set(labels, Wij);
    if(b){
        queue.add_point(Wij.n_to);
    }
    
}

void labels_update2_priority(std::vector<Label_set> &labels, Arc &Wij,Queue_priority &queue,std::vector<std::vector<float>> &borders){
    bool b = add_pareto_set(labels, Wij);
    if(b){

        queue.push(Queue_elt(Wij.n_to, labels[Wij.n_to], borders));
    }
    
}
 

bool add_pareto_set(std::vector<Label_set> &labs,Arc &Wij){

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
            new_label_set.add_point_at_end(    Label((*it_i).getX() + Wij.weights[0],(*it_i).getY() + Wij.weights[1],Wij.n_from)   );
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
                
                new_label_set.add_point_at_end( Label((*it_i).getX() + Wij.weights[0],(*it_i).getY() + Wij.weights[1],Wij.n_from) );
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
                    new_label_set.add_point_at_end(  Label((*it_i).getX() + Wij.weights[0],(*it_i).getY() + Wij.weights[1],Wij.n_from)  );
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



bool Label_set::add_point(float x, float y,  int pred){
    
    /*
    1 - On le place dans la liste selon sa coordonnée x
    2 - On compare au point d'avant 
        --> si y>=y_precedent, on suprime x,y et on return
    3 - On compare au point suivant :
        --> Si y>y_suivant, on return 
        --> Si y=y_suivant, on supprime le point suivant, qui est faiblement dominé, et on return
        --> Si y<y_suiant, on supprime tout le points i suivant tq : y<yi, on return 


    */


    if (set.size() == 0) {
        set.push_back(Label(x,y,pred)); 
        return true;     
    }

    

    auto it = set.begin();
    int i = 0;
    int state = 0;

    for(; it!=set.end(); ++it) {
        if((*it).getX() == x ) {
            state = 1;

            break;
        }
        if((*it).getX() > x ) {
            i --;
            it --;
            state = 2;
            break;
        }
        ++i; 
    }

    auto next_it = it;
    next_it++;
    auto next_next_it = next_it;
    next_next_it++;


    //Cas ou l'élement doit être ajouté à la fin
    if (state == 0) {
        
        if (y>= (*(std::prev(set.end()))).getY()) {
            return false;
        }
        set.push_back(Label(x,y,pred)); 
        return true;
    }

    //cas ou l'élement est comprise entre 2 valeurs du set selon x
    if(state == 2) {
        
        if (i>= 0 && y>= (*it).getY()) { //ie : quand on est pas sur le 1er élement
            return false;
        }

        if(y>(*next_it).getY()) {
            set.insert(next_it,Label(x,y,pred));
            return true;
        }
        if(y == (*next_it).getY()) {
            
            *next_it = Label(x,y,pred);
            return true;
        }
        if(y< (*next_it).getY()) {
            *next_it = Label(x,y,pred);
        
            while(i+2< set.size() && y<= (*next_next_it).getY()) {
                set.erase(next_next_it);
                ++next_next_it;
            }
            return true;
        }
    }

    //Cas ou l'élement à la même valeur de x qu'un autre éleement du set
    if(state == 1) {
        if(y>= (*it).getY()) {
            return false;
        }
        if(y<(*it).getY()) {
            *it = Label(x,y,pred);
            while(i+1< set.size() && y<= (*next_it).getY()) {
                set.erase(next_it);
                ++next_it;

            }
            return true;
        }
    }
    return false;
}

void Label_set::add_point_at_end(Label label){
    set.push_back(label); 
};

Label Label_set::get_last(){
    return set.back();
};

float Label_set::calculate_AUC(std::vector<std::vector<float>> &borders, int i){
    float auc = 0;
    auto it = set.begin();
    if (it == set.end()) {return 0;}
    float lx =(*it).getX();
    float ly =(*it).getY();
    
    auc += (lx-borders[0][i])*(borders[2][i] - borders[1][i]);



    ++it;
    while (it != set.end()) {
        
        auc += (static_cast<float>((*it).getX()-lx))*(static_cast<float>(ly-borders[1][i]));
        lx =(*it).getX();
        ly =(*it).getY();
        ++it;

    }
    auc += (borders[3][i]-lx)*(ly-borders[1][i]);
    //return 1 - auc/((borders[3][i]-borders[0][i])*(borders[2][i]-borders[1][i]));
    return auc;

};


bool Queue_elt::operator<(const Queue_elt& other) const {
    return auc < other.auc;
   
};

void Queue_priority::push(const Queue_elt& elt) {
    pq.push(elt);
};

Queue_elt Queue_priority::top() {
    if (!pq.empty()) {
        return pq.top();
    } else {
        throw std::out_of_range("La queue est vide");
    }
};

int Queue_priority::size(){
    return pq.size();
}

void Queue_priority::pop() {
    if (!pq.empty()) {
        pq.pop();
    } else {
        throw std::out_of_range("La queue est vide");
    }
};

bool Queue_priority::empty() const {
    return pq.empty();
};



void Queue::add_point(int i){
    for(int k = 0;k<queue_list.size();k++) {
        if (queue_list[k] == i){
            return;
        } 
        // if (queue_list[k] > i) {
        //     queue_list.insert(queue_list.begin()+k,i);
        //     return;
        // } 
    }
    queue_list.push_back(i);
    return;


};
void Queue::remove_point(int i){
    for(int k = 0;k<queue_list.size();k++){
        if (queue_list[k] == i) {
            queue_list.erase(queue_list.begin()+k);
            return;
        } 
        if (queue_list[k] > i) {
            return;
        } 
    }
};
void Queue::print() {
    std::cout<<"print :"<<std::endl;
    for(int k = 0;k<queue_list.size();k++){
        std::cout<< queue_list[k]<<std::endl;
    }
}

int Queue::random_choice(){
    std::random_device rd;  // Pour obtenir une graine aléatoire
    std::mt19937 gen(rd()); // Mersenne Twister pour générer des nombres pseudo-aléatoires
    std::uniform_int_distribution<> dis_int(0, queue_list.size()-1);
    int val = dis_int(gen);
    int i = queue_list[val];
    queue_list.erase(queue_list.begin()+val);
    
    return i;
}

int Queue::first_choice(){
    int i = queue_list[0];
    queue_list.erase(queue_list.begin());
    return i;
}

int Queue::size(){
    return queue_list.size();
}


void dijkstra_bin(Multigraph g, int s, int strategy, bool display) {
    
    if (g.dim !=2) {
        print_and_exit("dijkstra_bin : La dimension n'est pas de 2");
    }
    //Labels
    std::vector<Label_set> labels = std::vector<Label_set>(g.N, Label_set());
    labels[s].add_point(0,0,s);

    //Queue
    Queue q = Queue();
    q.add_point(s);


    float counter = 0;
    float total_l =1;
    auto start = Clock::now();
    auto end = Clock::now();
    auto start1 = Clock::now();
    auto end1 = Clock::now();
    auto start2 = Clock::now();
    auto end2 = Clock::now();

    auto durations = std::vector<Duration>(3,Duration(0));


    while(q.size() >0) {
        counter++;
        start = Clock::now();
        start1 = Clock::now();
        int pivot;
        if (strategy ==1) {
            pivot = q.first_choice();
        } else {
            pivot = q.random_choice();
        }
        total_l += q.size();
        end1 = Clock::now();
        start2 = Clock::now();
        for (int succ = 0;succ<g.N; ++succ) {
            if(g.A_bool[pivot][succ] == 1) {
                labels_update2(labels,g.A[pivot][succ], q);
            }
        }
        end2 = Clock::now();
        end = Clock::now();

        durations[0] += end - start;
        durations[1] += end1 - start1;
        durations[2] += end2 - start2;

    }
    std::cout
    <<"In while loop : \nqueue : "<<durations[1].count()/durations[0].count()
    << "\nupdate : "<<durations[2].count()/durations[0].count()
    <<"\naverage total : "<<total_l/counter
    <<"counter : "<<counter
    <<std::endl;

    if (display) {
        for(int i =0; i<g.N; ++i) {
            std::cout<<"|||||||||||||||||||"<<std::endl;
            std::cout<<"NODE "<<i<<std::endl;
            labels[i].print();
        }
    }

    std::ofstream outFile("../save/graph_to_plot/solution");
    outFile<<g.N<<std::endl;
    for (int i = 0;i<g.N;i++) {
        for(auto it = labels[i].set.begin();it!=labels[i].set.end();++it) {
            outFile<<(*it).getX()<< " "<<(*it).getY()<<" "<<(*it).getPred()<<std::endl;
        }
        outFile<<"*"<<std::endl;
    }
    
    
    
}

void dijkstra_AUC(Multigraph g, int s, bool display) {
    
    if (g.dim !=2) {
        print_and_exit("dijkstra_bin : La dimension n'est pas de 2");
    }
    //Labels
    std::vector<Label_set> labels = std::vector<Label_set>(g.N, Label_set());
    labels[s].add_point(0,0,s);

    std::vector<std::vector<float>> borders = dijkstra_1D(g, s);

    //Queue
    Queue_priority q = Queue_priority();
    q.push(Queue_elt(s, labels[s], borders));

    


    float counter = 0;
    float total_l =1;
    auto start = Clock::now();
    auto end = Clock::now();
    auto start1 = Clock::now();
    auto end1 = Clock::now();
    auto start2 = Clock::now();
    auto end2 = Clock::now();

    auto durations = std::vector<Duration>(3,Duration(0));


    while(q.size() >0) {
        counter++;
        start = Clock::now();
        start1 = Clock::now();

        Queue_elt pivot = q.top();
        q.pop();


        total_l += q.size();
        end1 = Clock::now();
        start2 = Clock::now();
        for (int succ = 0;succ<g.N; ++succ) {
            if(g.A_bool[pivot.n][succ] == 1) {
                labels_update2_priority(labels,g.A[pivot.n][succ], q, borders);
            }
        }
        end2 = Clock::now();
        end = Clock::now();

        durations[0] += end - start;
        durations[1] += end1 - start1;
        durations[2] += end2 - start2;

    }
    std::cout
    <<"In while loop : \nqueue : "<<durations[1].count()/durations[0].count()
    << "\nupdate : "<<durations[2].count()/durations[0].count()
    <<"\naverage total : "<<total_l/counter
    <<"counter : "<<counter
    <<std::endl;

    if (display) {
        for(int i =0; i<g.N; ++i) {
            std::cout<<"|||||||||||||||||||"<<std::endl;
            std::cout<<"NODE "<<i<<std::endl;
            labels[i].print();
        }
    }
    
    
    
}

std::vector<std::vector<float>> dijkstra_1D(Multigraph g, int s) {
    if (g.dim != 2) {
        print_and_exit("dijkstra_1D : dimension pas égale à 2");
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
        
        //recherche de l'indice du minimum :
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

        //traitement des voisins :
        for (int j = 0;j<g.N;j++) {
            if (g.A_bool[*it_max1][j]){
                if (dists[0][j]>dists[0][*it_max1] +g.A[*it_max1][j].weights[0]){
                    dists[0][j] = dists[0][*it_max1] +g.A[*it_max1][j].weights[0];
                    preds[0][j] = *it_max1;
                }
            }
            if (g.A_bool[*it_max2][j]){
                if (dists[1][j]>dists[1][*it_max2] +g.A[*it_max2][j].weights[1]){
                    dists[1][j] = dists[1][*it_max2] +g.A[*it_max2][j].weights[1];
                    preds[1][j] = *it_max2;
                }
            }
        }

        

    }
    int ind;
    float count;
    for(int i =0;i<g.N; ++i) {

        ind = i;
        count = 0;
        while(ind !=s) {

            count += g.A[preds[0][ind]][ind].weights[1];
            ind = preds[0][ind];
        }
        dists[2][i] = count;

        ind = i;
        count = 0;
        while(ind!=s) {
            count += g.A[preds[1][ind]][ind].weights[0];
            ind = preds[1][ind];
        }
        dists[3][i] = count;


    }

    return dists;

}