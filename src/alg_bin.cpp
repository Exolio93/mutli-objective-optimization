#include "../include/alg_bin.hpp"


int Label_bin::getX(int i){
    return std::get<0>(std::get<0>(set[i]));
}
int Label_bin::getY(int i){
    return std::get<1>(std::get<0>(set[i]));
}
int Label_bin::getPred(int i){
    return std::get<1>(set[i]);
}
void Label_bin::print(){
    std::cout<<"-----"<<std::endl;
    for(int i = 0; i<set.size(); ++i) {
        std::cout<<"x:"<<getX(i)<< " y:"<<getY(i)<<" pred:"<<getPred(i)<<std::endl;
    }
    std::cout<<"-----"<<std::endl;

}



void labels_update(std::vector<Label_bin> &labels, int i, int j, Arc &Wij,Queue &queue){
    bool b = false;
    
    for(int k=0; k<labels[i].set.size(); ++k) {
        b = labels[j].add_point(labels[i].getX(k) + Wij.weights[0],labels[i].getY(k) + Wij.weights[1], i)|| b;
    }
    if(b) {
        queue.add_point(j);
    }
    
}


bool Label_bin::add_point(int x, int y,  int pred){
    
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
        set.push_back(std::make_tuple(std::make_tuple(x,y), pred)); 
        return true;     
    }

    

    int i = 0;
    int state = 0;

    for(; i<set.size(); ++i) {
        if(getX(i) == x ) {
            state = 1;

            break;
        }
        if(getX(i) > x ) {
            i --;
            state = 2;
            break;
        } 
    }
    //Cas ou l'élement doit être ajouté à la fin
    if (state == 0) {
        if (y>= getY(set.size()-1)) {
            return false;
        }
        set.push_back(std::make_tuple(std::make_tuple(x,y), pred)); 
        return true;
    }

    //cas ou l'élement est comprise entre 2 valeurs du set selon x
    if(state == 2) {
        
        if (i>= 0 && y>= getY(i)) { //ie : quand on est pas sur le 1er élement
            return false;
        }

        if(y>getY(i+1)) {
            set.insert(set.begin()+i+1,std::make_tuple(std::make_tuple(x,y), pred));
            return true;
        }
        if(y == getY(i+1)) {
            
            set[i+1] = std::make_tuple(std::make_tuple(x,y), pred);
            return true;
        }
        if(y< getY(i+1)) {
            set[i+1] = std::make_tuple(std::make_tuple(x,y), pred);
    
            while(i+2< set.size() && y<= getY(i+2)) {
                set.erase(set.begin()+i+2);
            }
            return true;
        }
    }

    //Cas ou l'élement à la même valeur de x qu'un autre éleement du set
    if(state == 1) {
        if(y>= getY(i)) {
            return false;
        }
        if(y<getY(i)) {
            set[i] = std::make_tuple(std::make_tuple(x,y), pred);
            while(i+1< set.size() && y<= getY(i+1)) {
                set.erase(set.begin()+i+1);
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
    std::vector<Label_bin> labels = std::vector<Label_bin>(g.N, Label_bin());
    labels[s].add_point(0,0,s);

    //Queue
    Queue q = Queue();
    q.add_point(s);

    while(q.size() >0) {
        int pivot;
        if (strategy ==1) {
            pivot = q.max_it_choice();
        } else {
            pivot = q.random_choice();
        }

        for (int succ = 0;succ<g.N; ++succ) {
            if(g.A_bool[pivot][succ] == 1) {

                labels_update(labels,pivot, succ, g.A[pivot][succ], q);
            }
        }

    }
    if (display) {
        for(int i =0; i<g.N; ++i) {
            std::cout<<"|||||||||||||||||||"<<std::endl;
            std::cout<<"NODE "<<i<<std::endl;
            labels[i].print();
        }
    }
    
    
    
}