import matplotlib.pyplot as plt
import random as r
class Label:
    def __init__(self, x, y):
        self.x = x
        self.y = y


#TreeNode(xt,yt,xb,yb)
#TreeNode(lab)
class TreeNode: 
    def __init__(self, xt= None, yt= None, xb= None, yb = None, lab = None):
        self.label = lab
        self.left = None
        self.right = None
        if (lab == None):
            self.xt = xt
            self.yt = yt
            self.xb = xb
            self.yb = yb
        else:
            self.xt = None
            self.yt = None
            self.xb = None
            self.yb = None
        
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
            
    def test_insertion(self,x,y):
        if self.label:
            return True
        if (x>=self.xb and y>= self.yt) or (x>=self.xt and y>= self.yb):
            return False
        if x<=self.xb or y<=self.yb :
            return True
        
        return self.left.test_insertion(x,y) and self.right.test_insertion(x,y)
                
    def cut_branch(self,x, y):
        if self.label:
            if self.label.x>= x and self.label.y >= y:
                plt.scatter([self.label.x],[self.label.y], c='red', marker = "x")
                return True
            return False
        if (x>=self.xb and y>= self.yt) or (x>=self.xt and y>= self.yb):
            return False
        if (x<=self.xb and y<= self.yb):
            self.left = None
            self.right = None
            plt.scatter([self.xt],[self.yt], c='red', marker = "x")
            plt.scatter([self.xb],[self.yb], c='red', marker = "x")
            return True
        
        
        if self.left.cut_branch(x,y) :
            self.left = False
        if self.right.cut_branch(x,y) :
            self.right = False
            
        return False
        
    
    
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
    n = 7
    l = []
    for k in range(n):
        l.append(Label(k,n-1-k))
        
    bt2 = create_balanced_tree(l)
    
    
    
    
    
    # for k in range(0,101):
    #     rdm = r.uniform(-1,1)
    #     x = (n-1)*k/100
    #     y=n-1-x+rdm
    #     if bt2.test_insertion(x,y):
    #         plt.scatter([x], [y], c="gray", marker = 'o')
    #     else : 
    #         plt.scatter([x], [y], c="gray", marker = 'x')
    
    
    
    x,y = 1.8,1.8
    bt2.plot()
    bt2.cut_branch(x,y)
    plt.scatter([x], [y], c="gray", marker = 'x')
    plt.figure()
    bt2.plot()
    
    plt.show()



if __name__ == "__main__":
    main()
    
    