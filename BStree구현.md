```python
class Node:
    def __init__(self, key):    
        self.left = None
        self.right = None
        self.parent = None
        self.key = key

    def get_follower(self):     # 오른쪽 서브트리가 존재할 때만 실행해야 함.
        cur = self.right
        while cur.left:
            cur = cur.left
        return cur

    def popfrom(self, tree):    # 루트노드 재설정 기능을 갖도록 하기 위해 tree를 매개변수로 받는다.
        if self.right and self.left:            # 차수 2
            follower = self.get_follower()
            follower.popfrom(tree)
            follower.left = self.left
            follower.right = self.right
            follower.left.parent = follower
            follower.right.parent = follower
        elif self.right:                        # 차수 1
            follower = self.right
        elif self.left:                         # 차수 1
            follower = self.left
        else:                                   # 차수 0
            follower = None
                                                # 위쪽과의 관계. 모든 경우
        if follower:                                # 리프노드삭제가 아니었을 경우에만 추가실행
            follower.parent = self.parent
        if self == tree.root:                       # cur가 루트노드였을 경우
            tree.root = follower
        else:                                       # cur가 루트노드가 아닐 경우 
            if self.parent.key < self.key:
                self.parent.right = follower
            else:
                self.parent.left = follower

    def left_rotate(self):
        son = self.right
        parent = self.parent
        self.right = son.left       # 서브트리 떼주기
        if son.left:
            son.left.parent = self
        son.left = self             # 상하관계 재설정
        self.parent = son
        son.parent = parent         # 부모와의 관계
        if parent:
            if parent.key < self.key:
                parent.right = son
            else:
                parent.left = son

    def right_rotate(self):
        son = self.left
        parent = self.parent
        self.left = son.right       # 서브트리 떼주기
        if son.right:
            son.right.parent = self
        son.right = self            # 상하관계 재설정
        self.parent = son
        son.parent = parent         # 부모와의 관계
        if parent:
            if parent.key < self.key:
                parent.right = son
            else:
                parent.left = son   

    def insert_rebalance(self):     # 자신은 확정적으로 red, 부모가 red일지도 모르는 상황에서 실행
        if not self.parent:                 # 특이케이스. 루트노드일 경우 해당 노드의 색만 바꾸면 된다.
            self.isred = False
            return
        if not self.parent.isred: return    # 특이케이스2. 부모가 black이면 그대로 종료하면 된다.

        parent = self.parent
        grandpa = parent.parent
        if self.parent == grandpa.left:
            uncle = grandpa.right
        else:
            uncle = grandpa.left
            
        if uncle and uncle.isred:                               # case1
            self.parent.isred = False
            uncle.isred = False
            grandpa.isred = True
            grandpa.insert_rebalance()
        elif self == parent.right and parent == grandpa.left:   # case2-1-1, 왼-오 꺾임    
            parent.left_rotate()
            parent.insert_rebalance()
        elif self == parent.left and parent == grandpa.right:   # case2-1-2, 오-왼 꺾임
            parent.right_rotate()
            parent.insert_rebalance()
        else:                                                   # case2-2, 쭉 뻗은 경우
            if self == parent.left:                                 # 좌로 뻗음
                grandpa.right_rotate()
            else:                                                   # 우로 뻗음
                grandpa.left_rotate()
            grandpa.isred = True
            parent.isred = False

    def pop_rebalance(parent, x):
        '''특이한 점으로 문제지점의 부모가 메소드의 주체다. 따라서 문제지점이 root라면 재귀적 실행이 불가능함.
            x의 형제는 None이 아님이 자명하다'''
        # 기본형
        if x == parent.left:
            brother = parent.right
            if brother.isred:                               # case 2-4
                parent.left_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                parent.pop_rebalance(x)
                return
            elif brother.right and brother.right.isred:     # case *-2
                parent.left_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                brother.right.isred = False
                return
            elif brother.left and brother.left.isred:       # case *-3
                brother.right_rotate()
                brother.isred = True
                brother.parent.isred = False
                parent.pop_rebalance(x)
                return
        # 대칭형
        else:
            brother = parent.left
            if brother.isred:                               # case 2-4
                parent.right_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                parent.pop_rebalance(x)
                return
            elif brother.left and brother.left.isred:       # case *-2
                parent.right_rotate()
                parent.isred, brother.isred = brother.isred, parent.isred
                brother.left.isred = False
                return
            elif brother.right and brother.right.isred:     # case *-3
                brother.left_rotate()
                brother.isred = True
                brother.parent.isred = False
                parent.pop_rebalance(x)
                return   
        # case 1-1과 case 2-1만 남았다. 통합해서 시행한다.
        brother.isred = True
        if parent.isred:                                    # case 1-1
            parent.isred = False
        else:                                               # case 2-1
            if not parent.parent: return            # 루트노드라면 재귀실행이 필요없다.
            parent.parent.pop_rebalance(parent)
        
class BStree:
    def __init__(self):    
        self.root = None

    def find(self, key):
        cur = self.root
        while cur:
            if cur.key < key:
                cur = cur.right
            elif key < cur.key:
                cur = cur.left
            else: break
        return cur
        
    def insert(self, node):
        cur = self.root
        while cur:                          # cur가 node의 부모가 되는 지점까지 타고 내려가야 함.
            if cur.key < node.key:
                if cur.right:
                    cur = cur.right
                else:
                    cur.right = node
                    node.parent = cur
                    return
            elif node.key < cur.key:
                if cur.left:
                    cur = cur.left
                else:
                    cur.left = node
                    node.parent = cur
                    return
            else:
                print('key {} already in tree'.format(node.key))
                return
            
        self.root = node        # 비어있는 트리였을 경우에만 위의 while문 대신 실행됨.
        return

    def pop(self, key):
        cur = self.find(key)
        if not cur:
            print('key {} not in tree'.format(key))
            return
        cur.popfrom(self)
        return cur
             
class RBtree(BStree):
    def insert(self, node):
        super().insert(node)
        node.isred = True
        node.insert_rebalance()             # 자신은 확정적으로 red, 부모가 red일지도 모르는 상황에서 리밸런스
        cur = self.root                     # 로테이션으로 인해 루트가 바뀌었을 가능성이 있으므로 실행해야 한다.
        while cur.parent:
            cur = cur.parent
        self.root = cur

    def pop(self, key):
        cur = self.find(key)
        if not cur:
            print('key {} not in tree'.format(key))
            return
        # 1. red 노드를 삭제하는 경우. rebalance 불필요.
        if cur.isred:
            cur.popfrom(self)
            return cur

        if cur.left and cur.right:
            follower = cur.get_follower()
            p_node = follower.right             # 문제가 될 노드를 마킹한다.
            if follower == cur.right:           # p_node가 None일 가능성이 있으므로 부모노드도 필요하다. p_parent도 None일 수 있음.
                p_parent = follower
            else:
                p_parent = follower.parent          
        else:
            if cur.left:
                follower = cur.left
            else:
                follower = cur.right
            p_node = follower
            p_parent = cur.parent

        cur.popfrom(self)
        # 2. black를 삭제하더라도 후계자가 red이면 색깔 바꿔주고 끝난다.
        if follower and follower.isred:
            follower.isred = False
            return cur
        # 3. 자신과 후계자 모두 black. 문제가 발생하는 경우다.
        if p_node and p_node.isred:         # 문제노드가 후계자와 다르면서 색깔이 red일 수 있다. 색깔 바꾸고 끝낸다.
            p_node.isred = False
            return cur
        
        if p_parent:                        # 문제지점이 루트노드가 아닌 경우만 고려.(루트노드였다면 어차피 black인 경우만 남아서 할 게 없다.)
            p_parent.pop_rebalance(p_node)
            ascender = self.root            # 로테이션으로 인해 루트가 바뀌었을 가능성이 있으므로 실행해야한다
            while ascender.parent:
                ascender = ascender.parent
            self.root = ascender
        return cur
