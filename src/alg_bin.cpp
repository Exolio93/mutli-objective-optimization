#include "../include/alg_bin.hpp"
#include<chrono>
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

int Label::getX() const{
    return x;
}
int Label::getY() const{
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



void labels_update(std::vector<Label_set> &labels, int i, int j, Arc &Wij,Queue &queue){
    bool b = false;
    auto it = labels[i].set.begin();
    for(int k=0; k<labels[i].set.size(); ++k) {
        int wx = (*it).getX();
        int wy = (*it).getY();
        b = labels[j].add_point(wx + Wij.weights[0], wy + Wij.weights[1], i)|| b;
        ++it;
    }
    if(b) {
        queue.add_point(j);
    }
    
}

void Label_set::add_set(Label_set &lab_i, Arc &Wij){

}


bool Label_set::add_point(int x, int y,  int pred){
    
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



void Queue::add_point(int i){
    for(int k = 0;k<queue_list.size();k++) {
        if (queue_list[k][0] == i) {
            queue_list[k][1]++;
            return;
        } 
        if (queue_list[k][0] > i) {
            queue_list.insert(queue_list.begin()+k,{i,1});
            return;
        } 
    }
    queue_list.push_back({i,1});
    return;


};
void Queue::remove_point(int i){
    for(int k = 0;k<queue_list.size();k++){
        if (queue_list[k][0] == i) {
            queue_list.erase(queue_list.begin()+k);
            return;
        } 
        if (queue_list[k][0] > i) {
            return;
        } 
    }
};
void Queue::print() {
    std::cout<<"print :"<<std::endl;
    for(int k = 0;k<queue_list.size();k++){
        std::cout<< queue_list[k][0]<< " "<< queue_list[k][1]<<std::endl;
    }
}

int Queue::random_choice(){
    std::random_device rd;  // Pour obtenir une graine aléatoire
    std::mt19937 gen(rd()); // Mersenne Twister pour générer des nombres pseudo-aléatoires
    std::uniform_int_distribution<> dis_int(0, queue_list.size()-1);
    int val = dis_int(gen);
    int i = queue_list[val][0];
    queue_list.erase(queue_list.begin()+val);
    
    return i;
}
int Queue::max_it_choice(){
    int ind_max = 0;
    for(int k = 1;k<queue_list.size();k++){
        if (queue_list[k][1] >queue_list[ind_max][1]) {
            ind_max = k;
        }
    }
    int i = queue_list[ind_max][0];
    queue_list.erase(queue_list.begin()+ind_max);
    
    return i;
}
int Queue::size(){
    return queue_list.size();
}


int choose_node(std::vector<int> &L){
    if (L.size() == 0) {
        print_and_exit("choose_node : L is empty");
    }
    int s = L.back();
    //std::cout<<"On a choisit : "<<s<<std::endl;
    L.pop_back();
    return s;
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
            pivot = q.max_it_choice();
        } else {
            pivot = q.random_choice();
        }
        total_l += q.size();
        end1 = Clock::now();
        start2 = Clock::now();
        for (int succ = 0;succ<g.N; ++succ) {
            if(g.A_bool[pivot][succ] == 1) {
                labels_update(labels,pivot, succ, g.A[pivot][succ], q);
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
    <<std::endl;

    if (display) {
        for(int i =0; i<g.N; ++i) {
            std::cout<<"|||||||||||||||||||"<<std::endl;
            std::cout<<"NODE "<<i<<std::endl;
            labels[i].print();
        }
    }
    
    
    
}