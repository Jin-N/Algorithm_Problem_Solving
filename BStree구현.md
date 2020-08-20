```python
class BStree:
    def __init__(self, *args):    
        self.left = None
        self.right = None
        self.parent = None
        if args:
            if type(args[0]) == list:
                self.val = float('inf')
                for val in args[0]:
                    self.insert(val)
            else:
                self.val = args[0]
        else:
            self.val = float('inf')

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
        if self.val < val:                          # bigger
            if self.right:
                self.right.remove(val)
            else:
                raise ValueError('{} not in tree'.format(val))
                
        elif val < self.val:                        # smaller
            if self.left:
                self.left.remove(val)
            else:
                raise ValueError('{} not in tree'.format(val))
                
        else:                                       # equal
            if self.right == self.left == None:     # leaf
                if self.parent.val < self.val:
                    self.parent.right = None
                else:
                    self.parent.left = None
                    
            elif self.right == None or self.left.right == None: # pull up left node
                self.left.parent = self.parent
                if self.parent.val < self.val:
                    self.parent.right = self.left
                else:
                    self.parent.left = self.left
                    
                if self.right:
                    self.left.right = self.right
                    self.right.parent = self.left
            
                    
            elif self.left == None or self.right.left == None: # pull up right node 
                self.right.parent = self.parent
                if self.parent.val < self.val:
                    self.parent.right = self.right
                else:
                    self.parent.left = self.right
                    
                if self.left:
                    self.right.left = self.left
                    self.left.parent = self.right
                    
                    
            else:                                   # full with good children
                R = self.right
                while R.left:
                    R = R.left
                
                R.parent.left = R.right
                if R.right:
                    R.right.parent = R.parent
                
                R.parent = self.parent
                if self.parent.val < self.val:
                    self.parent.right = R
                else:
                    self.parent.left = R
                        
                R.left = self.left
                self.left.parent = R
                
                R.right = self.right
                self.right.parent = R
                     
arr = [10, 5, 15, 3, 7, 12, 17, 1, 4, 6, 8, 11, 13, 18]   
         
tree = BStree(arr)    
tree.remove(10)


def inorder(root):
    if root == None: return
    
    inorder(root.left)
    print(root.val)
    inorder(root.right)
    
inorder(tree)

```

