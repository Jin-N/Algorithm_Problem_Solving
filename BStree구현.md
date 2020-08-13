```python
class BStree:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
        
    def insert(self, val):
        if self.val < val:
            if self.right: 
                self.right.insert(val)
            else: 
                self.right = BStree(val)
                self.right.parent = self
        elif val < self.val:
            if self.left:
                self.left.insert(val)
            else:
                self.left = BStree(val)
                self.left.parent = self           
        else:
            raise ValueError('{} already in tree'.format(val))
    
    def remove(self, val):
        if self.val < val:
            if self.right:
                self.right.remove(val)
            else:
                raise ValueError('{} not in tree'.format(val))
                
        elif val < self.val:
            if self.left:
                self.left.remove(val)
            else:
                raise ValueError('{} not in tree'.format(val))
                
        else:
            if self.right == self.left == None:
                if self.parent.val < self.val:
                    self.parent.right = None
                else:
                    self.parent.left = None
                    
            elif self.right == None:
                self.left.parent = self.parent
                if self.parent.val < self.val:
                    self.parent.right = self.left
                else:
                    self.parent.left = self.left
                    
            elif self.left == None:
                self.right.parent = self.parent
                if self.parent.val < self.val:
                    self.parent.right = self.right
                else:
                    self.parent.right = self.right
    
            
                
arr = [1, 2, 4, 5, 3]   

def inorder(root):
    if root == None: return
    
    inorder(root.left)
    print(root.val)
    inorder(root.right)
                
tree = BStree(arr[0])
for val in arr[1:]:
    tree.insert(val)
    
tree.remove(3)
    
inorder(tree)


```

