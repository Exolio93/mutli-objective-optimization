import matplotlib.pyplot as plt
import random as r
import time as t
class Label:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.isIns = False;
#TreeNode(xt,yt,xb,yb)
#TreeNode(lab)
class TreeNode: 
    def __init__(self, xt= None, yt= None, xb= None, yb = None, lab = None):
        self.label = lab
        self.left = None
        self.right = None
        self.isInserted = False
        if (lab == None):
            self.xt = xt
            self.yt = yt
            self.xb = xb
            self.yb = yb
        else:
            self.xt = lab.x
            self.yt = lab.y
            self.xb = lab.x
            self.yb = lab.y
        
        self.root = None
        
    def add_internal_node(self, xt, yt, xb, yb, is_left):
        node = TreeNode(xt, yt, xb, yb)
        if is_left:
            self.left = node
        else:
            self.right = node

    def add_leaf(self, label, is_left):
        leaf = TreeNode(lab=label)
        if is_left:
            self.left = leaf
        else:
            self.right = leaf

    def inorder_traversal(self):
        if self.label:
            print(f"Label: {self.label.x}, {self.label.y}")
            return 
        print(f"Internal Node: ({self.xt}, {self.yt})")
        if self.left:
            self.left.inorder_traversal()        
        
        if self.right:
            self.right.inorder_traversal()
                
                
    def plot(self):
        if self.label:
            plt.scatter([self.label.x],[self.label.y], c='yellow')
            return (self.label.x, self.label.y, self.label.x, self.label.y)
        
        plt.scatter([self.xt],[self.yt], c='blue')
        plt.scatter([self.xb],[self.yb], c='green')
        
        if self.left:
            xt,yt,xb,yb = self.left.plot()
            plt.plot([self.xt,xt ],[self.yt, yt], color='blue', linestyle='--')
            plt.plot([self.xb,xb ],[self.yb, yb], color='green', linestyle='--')
            
        
        if self.right:
            xt,yt,xb,yb = self.right.plot()
            plt.plot([self.xt,xt ],[self.yt, yt], color='blue', linestyle='--')
            plt.plot([self.xb,xb ],[self.yb, yb], color='green', linestyle='--')
        
        return self.xt, self.yt, self.xb, self.yb

    def remove_and_insert(self,lab):
        insert_without_cutting = False
        if ((lab.x > self.xt and lab.y <self.yb) or (lab.x<self.xb and lab.y>self.yt)):
            insert_without_cutting = True
            
            
        if self.label:
            if self.label.x>= lab.x and self.label.y >= lab.y:
                if lab.isIns :
                    return None, False
                
                else : 
                    lab.isIns = True
                    self.label = lab
                    self.xt = lab.x
                    self.yt = lab.y
                    self.xb = lab.x
                    self.yb = lab.y
                    return self,False
            else : 
                return self, insert_without_cutting
        if (lab.y> self.yt) or (lab.x>self.xt):
            return self,insert_without_cutting
        if (lab.x<=self.xb and lab.y<= self.yb):
            self.left = None
            self.right = None
            if lab.isIns :
                return None,False
            else : 
                lab.isIns = True
                self.label = lab
                self.xt = lab.x
                self.yt = lab.y
                self.xb = lab.x
                self.yb = lab.y
                return self,False
        
        left_child,left_bool = self.left.remove_and_insert(lab)
        right_child,right_bool = self.right.remove_and_insert(lab)
        
        self.left = left_child
        self.right = right_child
        
        
        if( left_bool and right_bool and not lab.isIns):
            lab.isIns = True
            if r.uniform(0,1)>0.5:
                node = TreeNode(self.xt, lab.y, lab.x, self.yb)
                node.add_leaf(lab,True)
                node.right = right_child
                self.right = node
            else:
                node = TreeNode(lab.x, self.yt, self.xb, lab.y)
                node.add_leaf(lab,False)
                node.left = left_child
                self.left = node
                
                
    
        if right_child == None and left_child == None : 
            return None,False
        
        elif right_child == None :
             
            return left_child,False
        
        elif left_child == None : 
            return right_child,False
        
        else : 
            self.xb = left_child.xb
            self.yb = right_child.yb
            self.xt = right_child.xt
            self.yt = left_child.yt
            return self,insert_without_cutting

        
def merge_fronts(tree_1, tree_2, allow_to_insert):
    #tree_1 is label
    if (tree_1.label):
        tree_2.remove_and_insert(tree_1.label)
        return tree_2
    
    #tree_2 is label
    if (tree_2.label):
        tree_1.remove_and_insert(tree_2.label)
        return tree_1
    
    #tree_2 dominate tree_1
    if (tree_2.xt<= tree_1.xb and tree_2.yt<=tree_1.yb):
        return tree_2
    
    #tree_1 dominate tree_2
    if (tree_2.xb>= tree_1.xt and tree_2.yb>=tree_1.yt):
        return tree_1
    
    
    if (tree_2.xb>= tree_1.xt and tree_2.yt<=tree_1.yb and allow_to_insert):
        node = TreeNode(tree_2.xt, tree_1.yt, tree_1.xb, tree_2.yb)
        node.left = tree_1
        node.right = tree_2
        return node
    
    if (tree_2.xt<= tree_1.xb and tree_2.yb>=tree_1.yt and allow_to_insert):
        node = TreeNode(tree_1.xt, tree_2.yt, tree_2.xb, tree_1.yb)
        node.left = tree_2
        node.right = tree_1
        return node
    
    # tree_2 inside tree_1
    if (tree_2.xt>= tree_1.xt and tree_2.xb<= tree_1.xb and tree_2.yt>= tree_1.yt and tree_2.yb<=tree_1.yb):
        b = r.uniform(0,1)>0.5
        tree_left = merge_fronts(tree_1.left, tree_2, b)
        tree_right = merge_fronts(tree_1.right, tree_2, not b)
            
        node = TreeNode(tree_left.xt, tree_right.yt, tree_right.xb, tree_left.yb)
        node.left = tree_left
        node.right = tree_right
        return node
    
    
    # tree_1 inside tree_2
    if (tree_1.xt>= tree_2.xt and tree_1.xb<= tree_2.xb and tree_1.yt>= tree_2.yt and tree_1.yb<=tree_2.yb):
        b = r.uniform(0,1)>0.5
        tree_left = merge_fronts(tree_1, tree_2.left, b)
        tree_right = merge_fronts(tree_1, tree_2.right, not b)
        node = TreeNode(tree_left.xt, tree_right.yt, tree_right.xb, tree_left.yb)
        node.left = tree_left
        node.right = tree_right
        return node
    
    size_1 = tree_1.yt - tree_1.yb + tree_1.xt-tree_1.yb
    size_2 = tree_2.yt - tree_2.yb + tree_2.xt-tree_2.yb
    
    #"else" case
    if (size_1>size_2):
       b = r.uniform(0,1)>0.5
        tree_left = merge_fronts(tree_1.left, tree_2, b)
        tree_right = merge_fronts(tree_1.right, tree_2, not b)
            
        node = TreeNode(tree_left.xt, tree_right.yt, tree_right.xb, tree_left.yb)
        node.left = tree_left
        node.right = tree_right
        return node 
        
        
        
    
    
def create_balanced_tree(l):
    if len(l) == 0 : 
        print("Any element in the label Set...")
        exit
    elif len(l) == 1 :
        return TreeNode(lab = l[0])
    else :
        node = TreeNode(l[-1].x, l[0].y, l[0].x, l[-1].y)
        node.left = create_balanced_tree(l[:len(l)//2])
        node.right = create_balanced_tree(l[len(l)//2:])
        
        return node
    
    



def main():
    # n_val = [1000,4000,12000,16000,32000,64000,128000,256000]
    # time_val = []
    
    # for n in n_val :
    #     print(n)
    #     l = []
        
    #     for k in range(n):
    #         l.append(Label(k,n-1-k))
            
    #     bt2 = create_balanced_tree(l)
    #     # bt2.plot()
    #     t1 = t.time()
    
    #     for k in range(0,50001):
    #         # rdm = r.uniform(-1,1)
    #         x = r.uniform(0,(n-1))
    #         y=n-1-x + r.uniform(-2,2)
    #         bt2.remove_and_try_insertion(Label(x,y))
            
    #         # if bt2.test_insertion(x,y):
    #         #     plt.scatter([x], [y], c="gray", marker = 'o')
    #         # else : 
    #         #     plt.scatter([x], [y], c="gray", marker = 'x')
    #     t2 = t.time()
    #     delta = t2-t1
    #     print(delta)
    #     time_val.append(delta)
    
        
    # # print(time_val)
    # plt.plot(n_val,time_val)
    # plt.show()
    #####################

    n = 4
    l = []
    for k in range(n):
        l.append(Label(k,n-1-k))

    bt2 = create_balanced_tree(l)  

    x,y = 1,1
    bt2.plot()
    
    bt2.remove_and_insert(Label(x,y))
    plt.scatter([x], [y], c="gray", marker = 'x')
    plt.figure()
    plt.scatter([x], [y], c="gray", marker = 'x')
    bt2.plot()
    
    plt.show()



if __name__ == "__main__":
    # main()
    
    root = create_balanced_tree([Label(2,5),Label(3,3),Label(4,2),Label(6,1)])
    root.remove_and_insert(Label(2.5,4))
    
    root.plot()
    plt.show()
    
    