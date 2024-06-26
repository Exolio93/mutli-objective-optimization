#include "../include/data_struct_2d.hpp"
#include<chrono>

float Label::getX() const{
    return x;
}
float Label::getY() const{
    return y;
}
int Label::getPred() const{
    return pred;
}
Label* Label::getLabelPred() const{
    return label_pred;
}

void Label_set::print(){
    std::cout<<"-----"<<std::endl;
    for(auto it = set.begin();it!=set.end();++it) {
        std::cout<<"x:"<<(*it).getX()<< " y:"<<(*it).getY()<<" pred:"<<(*it).getPred()<<std::endl;
    }
    std::cout<<"-----"<<std::endl;

}
 
bool Label_set::add_point(float x, float y,  int pred, Label* lab){
    
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
        set.push_back(Label(x,y,pred, lab)); 
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
        set.push_back(Label(x,y,pred,lab)); 
        return true;
    }

    //cas ou l'élement est comprise entre 2 valeurs du set selon x
    if(state == 2) {
        
        if (i>= 0 && y>= (*it).getY()) { //ie : quand on est pas sur le 1er élement
            return false;
        }

        if(y>(*next_it).getY()) {
            set.insert(next_it,Label(x,y,pred,lab));
            return true;
        }
        if(y == (*next_it).getY()) {
            
            *next_it = Label(x,y,pred,lab);
            return true;
        }
        if(y< (*next_it).getY()) {
            *next_it = Label(x,y,pred,lab);
        
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
            *it = Label(x,y,pred,lab);
            while(i+1< set.size() && y<= (*next_it).getY()) {
                set.erase(next_it);
                ++next_it;

            }
            return true;
        }
    }
    return false;
};
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

bool Heap_elt::operator<(const Heap_elt& other) const {
    return auc < other.auc;
   
};
Heap_elt Heap::top() {
    if (!pq.empty()) {
        return pq.top();
    } else {
        throw std::out_of_range("La queue est vide");
    }
};

void Heap::push(const Heap_elt& elt) {
    pq.push(elt);
};

int Heap::size(){
    return pq.size();
}

void Heap::pop() {
    if (!pq.empty()) {
        pq.pop();
    } else {
        throw std::out_of_range("La queue est vide");
    }
};

bool Heap::empty() const {
    return pq.empty();
};



void Queue::add_point(int i){
    if (node_bool[i]) {
        return;
    }
    node_bool[i] = true;
    queue_list.push_back(i);
    return;


};

void Queue::print() {
    std::cout<<"print :"<<std::endl;
    for(int k = 0;k<queue_list.size();k++){
        std::cout<< queue_list[k]<<std::endl;
    }
}


int Queue::pick(){
    int i = queue_list[0];
    queue_list.erase(queue_list.begin());
    node_bool[i] = false;
    return i;
}

int Queue::size(){
    return queue_list.size();
}
