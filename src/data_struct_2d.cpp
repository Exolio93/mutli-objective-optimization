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
    if(node_bool[elt.n] == true){
        return;
    }
    node_bool[elt.n] = true;
    pq.push(elt);
};

int Heap::size(){
    return pq.size();
}

void Heap::pop() {
    if (!pq.empty()) {
        node_bool[pq.top().n] = 0;
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
    queue_list.push(i);
    return;


};



int Queue::pick(){
    int i = queue_list.front();
    queue_list.pop();
    node_bool[i] = false;
    return i;
}

int Queue::size(){
    return queue_list.size();
}

void TreeNode::print() const {
    
    if (isLeaf()) {

        std::cout << "--> (" << label->getX() << ", " << label->getY() << ")\n";
        return;
    } 

    std::cout << "[(" << xb << ", " << yb << ") to (" << xt << ", " << yt << ")]\n";

    if (left) {

        left->print();

    }
    if (right) {

        right->print();

    }

}

std::pair<TreeNode*, bool> TreeNode::insert_label(Label* lab) {
    bool insert_without_cutting = false;
    if ((lab->getX() > xt && lab->getY() < yb) || (lab->getX() < xb && lab->getY() > yt)) {
        insert_without_cutting = true;
    }

    if (label) {
        if (label->getX() >= lab->getX() && label->getY() >= lab->getY()) {
            if (lab->is_inserted) {
                return std::make_pair(nullptr, false);
            } else {
                lab->is_inserted = true;
                label = lab;
                xt = lab->getX();
                yt = lab->getY();
                xb = lab->getX();
                yb = lab->getY();
                return std::make_pair(this, false);
            }
        } else {
            return std::make_pair(this, insert_without_cutting);
        }
    }

    if (lab->getY() > yt || lab->getX() > xt) {
        return std::make_pair(this, insert_without_cutting);
    }

    if (lab->getX() <= xb && lab->getY() <= yb) {
        left = nullptr;
        right = nullptr;
        if (lab->is_inserted) {
            return std::make_pair(nullptr, false);
        } else {
            lab->is_inserted = true;
            label = lab;
            xt = lab->getX();
            yt = lab->getY();
            xb = lab->getX();
            yb = lab->getY();
            return std::make_pair(this, false);
        }
    }

    std::pair<TreeNode*, bool> left_couple =left->insert_label(lab);
    std::pair<TreeNode*, bool> right_couple =right->insert_label(lab);

    left = left_couple.first;
    right = right_couple.first;

    if (left_couple.second && right_couple.second && !lab->is_inserted) {

        lab->is_inserted = true;

        if (std::rand() / double(RAND_MAX) > 0.5) {
            TreeNode* node = new TreeNode(xt, lab->getY(), lab->getX(), yb);
            node->left = new TreeNode(lab);
            node->right = right;
            right = node;
            node->print();
        } else {
            TreeNode* node = new TreeNode(lab->getX(), yt, xb, lab->getY());
            node->right = new TreeNode(lab);
            node->left = left;
            left = node;
        }
    }

    if (!right && !left) {
        return std::make_pair(nullptr, false);
    } else if (!right) {
        return std::make_pair(left, false);
    } else if (!left) {
        return std::make_pair(right, false);
    } else {
        xb = left->xb;
        yb = right->yb;
        xt = right->xt;
        yt = left->yt;
        return std::make_pair(this, insert_without_cutting);
    }
}

/*

std::pair<std::shared_ptr<TreeNode>, bool> TreeNode::insert_label(Label& lab) {
    std::cout<<"OK"<<std::endl;
    bool insert_without_cutting = false;
    if ((lab.getX() > this->xt && lab.getY() < this->yb) || (lab.getX() < this->xb && lab.getY() > this->yt)) {
        insert_without_cutting = true;
    }

    if (this->label) {
        if (this->label->getX() >= lab.getX() && this->label->getY() >= lab.getY()) {
            if (lab.is_inserted) {
                return std::make_pair(nullptr, false);
            } else {
                lab.is_inserted = true;
                this->label = std::make_unique<Label>(lab);
                this->xt = lab.getX();
                this->yt = lab.getY();
                this->xb = lab.getX();
                this->yb = lab.getY();
                return std::make_pair(std::make_shared<TreeNode>(std::move(*this)), false);
            }
        } else {
            return std::make_pair(std::make_shared<TreeNode>(std::move(*this)), insert_without_cutting);
        }
    }

    if (lab.getY() > this->yt || lab.getX() > this->xt) {
        return std::make_pair(std::make_shared<TreeNode>(std::move(*this)), insert_without_cutting);
    }

    if (lab.getX() <= this->xb && lab.getY() <= this->yb) {
        this->left = nullptr;
        this->right = nullptr;
        if (lab.is_inserted) {
            return std::make_pair(nullptr, false);
        } else {
            lab.is_inserted = true;
            this->label = std::make_unique<Label>(lab);
            this->xt = lab.getX();
            this->yt = lab.getY();
            this->xb = lab.getX();
            this->yb = lab.getY();
            return std::make_pair(std::make_shared<TreeNode>(std::move(*this)), false);
        }
    }

    std::shared_ptr<TreeNode> left_child = this->left ? this->left : std::make_shared<TreeNode>(0, 0, 0, 0);
    std::shared_ptr<TreeNode> right_child = this->right ? this->right : std::make_shared<TreeNode>(0, 0, 0, 0);
    bool left_bool = this->left ? this->left->insert_label(lab).second : false;
    bool right_bool = this->right ? this->right->insert_label(lab).second : false;

    this->left = std::move(left_child);
    this->right = std::move(right_child);

    if (left_bool && right_bool && !lab.is_inserted) {
        lab.is_inserted = true;
        if (std::rand() / double(RAND_MAX) > 0.5) {
            auto node = std::make_shared<TreeNode>(this->xt, lab.getY(), lab.getX(), this->yb);
            node->label = std::make_unique<Label>(lab);
            node->right = std::move(this->right);
            this->right = std::move(node);
        } else {
            auto node = std::make_shared<TreeNode>(lab.getX(), this->yt, this->xb, lab.getY());
            node->label = std::make_unique<Label>(lab);
            node->left = std::move(this->left);
            this->left = std::move(node);
        }
    }

    if (!this->right && !this->left) {
        return std::make_pair(nullptr, false);
    } else if (!this->right) {
        return std::make_pair(this->left, false);
    } else if (!this->left) {
        return std::make_pair(this->right, false);
    } else {
        this->xb = this->left->xb;
        this->yb = this->right->yb;
        this->xt = this->right->xt;
        this->yt = this->left->yt;
        return std::make_pair(std::make_shared<TreeNode>(std::move(*this)), insert_without_cutting);
    }
}
*/