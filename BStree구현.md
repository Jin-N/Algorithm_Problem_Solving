```python
class BStree:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        
    def insert(self, val):
        if self.val < val:
            if self.right: 
                self.right.insert(val)
            else: 
                self.right = BStree(val)               
        else:
            if self.left:
                self.left.insert(val)
            else:
                self.left = BStree(val)

def inorder(root):
    if root == None: return
    
    inorder(root.left)
    print(root.val)
    inorder(root.right)
                
tree = BStree(arr[0])
for val in arr[1:]:
    tree.insert(val)
    
inorder(tree)

```

