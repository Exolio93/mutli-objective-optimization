#include "../include/alg_bin.hpp"

int Label::getX(){
    return data[0];
}
int Label::getY(){
    return data[1];
}
int Label::getPred(){
    return data[2];
}
void Label::print(){
    std::cout<<"label : ("<<getX()<< ","<<getY()<<","<<getPred()<<")"<<std::endl;
}



void Label_set::print(){
    std::cout<<"-----"<<std::endl;
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout<<"x:"<<(*it).getX()<< " y:"<<(*it).getY()<<" pred:"<<(*it).getPred()<<std::endl;
    }
    std::cout<<"-----"<<std::endl;

}



void Label_set::add_point_and_update(int x, int y,  int pred,Queue &queue,int j){
    
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
        queue.add_elt(j,Label(x,y,pred));
        return;     
    }

    

    int state = 0;
    auto it = set.begin();
    for(; it != set.end(); ++it) {
        if((*it).getX() == x ) {
            state = 1;

            break;
        }
        if((*it).getX() > x ) {
            it --;
            state = 2;
            break;
        } 


    }
    //Cas ou l'élement doit être ajouté à la fin
    if (state == 0) {
        if (y>= set.back().getY()) {
            return;
        }
        set.insert(it,Label(x,y,pred)); 
        queue.add_elt(j,Label(x,y,pred));
        return;
    }

    //cas ou l'élement est comprise entre 2 valeurs du set selon x
    if(state == 2) {
        
        if (it>= set.begin() && y>= (*it).getY()) { //ie : quand on est pas sur le 1er élement
            return;
        }

        if(y>(*(it+1)).getY()) {
            set.insert(it+1,Label(x,y,pred));
            queue.add_elt(j,Label(x,y,pred));
            return;
        }
        if(y == (*(it+1)).getY()) {
            
            *(it+1) = Label(x,y,pred);
            queue.add_elt(j,Label(x,y,pred));
            return;
        }
        if(y< (*(it+1)).getY()) {
            *(it+1) = Label(x,y,pred);
    
            while(it+2< set.end() && y<= (*(it+2)).getY()) {
                set.erase(it+2);
            }
            queue.add_elt(j,Label(x,y,pred));
            return;
        }
    }

    //Cas ou l'élement à la même valeur de x qu'un autre éleement du set
    if(state == 1) {
        if(y>= (*it).getY()) {
            return;
        }
        if(y<(*it).getY()) {
            *it = Label(x,y,pred);
            while(it+1< set.end() && y<= (*(it+1)).getY()) {
                set.erase(it+1);

            }
            queue.add_elt(j,Label(x,y,pred));
            return;
        }
    }
    return;
}


int Queue_elt::getNode(){
    return std::get<0>(elt);
};
Label Queue_elt::getLabel(){
    return std::get<1>(elt);
};

void Queue_elt::print() {
    std::cout<< getNode()<< " - "<< getLabel().getX()<<" "<<getLabel().getY()<<" "<<getLabel().getPred() <<std::endl;
}


void Queue::add_elt(int n, Label lab){
    queue_list.push_back(Queue_elt(n,lab));
    return;
};

int Queue::getNode(int i){
    return queue_list[i].getNode();
};

Label Queue::getLabel(int i){
    return queue_list[i].getLabel();
};

void Queue::print() {
    std::cout<<"print queue :"<<std::endl;
    for(int k = 0;k<queue_list.size();k++){
        std::cout<< getNode(k)<< " - "<< getLabel(k).getX()<<" "<<getLabel(k).getY()<<" "<<getLabel(k).getPred() <<std::endl;
    }
}

Queue_elt Queue::random_choice(){
    std::random_device rd;  // Pour obtenir une graine aléatoire
    std::mt19937 gen(rd()); // Mersenne Twister pour générer des nombres pseudo-aléatoires
    std::uniform_int_distribution<> dis_int(0, queue_list.size()-1);
    int val = dis_int(gen);
    Queue_elt l = queue_list[val];
    queue_list.erase(queue_list.begin()+val);
    
    return l;
}

Queue_elt Queue::lexicographic_choice(){
    int k_max = 0;
    for(int k = 1;k<size(); ++k) {
        if (queue_list[k]<queue_list[k_max]) {
            k_max = k;
        }
    }
    Queue_elt l = queue_list[k_max];
    queue_list.erase(queue_list.begin()+k_max);
    return l;
}

bool Queue_elt::operator<(Queue_elt& other){
        if (getLabel().getX()< other.getLabel().getX()) {return true;}
        if (getLabel().getX()== other.getLabel().getX()
            &&getLabel().getY() < other.getLabel().getY()) {
                return true;   
        }
        return false;
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
        print_and_exit("dijkstra_bin : La dimension n'est pas de 2"); }

    //Queue
    Queue q = Queue();

    //Labels
    std::vector<Label_set> labels = std::vector<Label_set>(g.N, Label_set());
    labels[s].add_point_and_update(0,0,s,q,s);

    

    while(q.size() >0) {
        Queue_elt pivot = Queue_elt();
        
        
        if (strategy==0) {
            pivot = q.random_choice();
        } else {
            pivot = q.lexicographic_choice();

        }
        
        

        for (int succ = 0;succ<g.N; ++succ) {
            if(g.A_bool[pivot.getNode()][succ] == 1) {

                labels[succ].add_point_and_update(
                    pivot.getLabel().getX() + g.A[pivot.getNode()][succ].weights[0],
                    pivot.getLabel().getY() + g.A[pivot.getNode()][succ].weights[1],
                    pivot.getNode(),q,succ);
            }
        }

    }
    if (display) {
        std::cout<<"oooooooooooooooooooooo\noooooooooooooooooooooo"<<std::endl;
        for(int i =0; i<g.N; ++i) {
            std::cout<<"|||||||||||||||||||"<<std::endl;
            std::cout<<"NODE "<<i<<std::endl;
            labels[i].print();
        }
    }
    
    
    
    
}