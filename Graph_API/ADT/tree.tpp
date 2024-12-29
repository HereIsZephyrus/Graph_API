//
//  tree.cpp
//  Graph_API
//
//  Created by ChanningTong on 12/29/24.
//

using namespace tcb;
template <class Object,class TreeNode>
const BinarySearchTree<Object,TreeNode> & BinarySearchTree<Object,TreeNode>::operator = (const BST & rhs){
    if (this != &rhs){
        clear();
        this->root = clone(rhs.root);
    }
    return *this;
}
template <class Object,class TreeNode>
BinarySearchTree<Object,TreeNode>::BinarySearchTree(const BST & rhs) {
    if (this != &rhs){
        clear();
        this->root = clone(rhs.root);
    }
}
template <class Object,class TreeNode>
const Object& BinarySearchTree<Object,TreeNode>::findMin() const{
    if (this -> root == nullptr)
        throw std::logic_error("the tree is empty");
    return findMin(this->root)->element;
}
template <class Object,class TreeNode>
const Object& BinarySearchTree<Object,TreeNode>::findMax() const{
    if (this -> root == nullptr)
        throw std::logic_error("the tree is empty");
    return findMax(this->root)->element;
}
template <class Object,class TreeNode>
static ostream& BinarySearchTree<Object,TreeNode>::print(ostream& os, TreeNode* p){
    if (p == nullptr)
        return os;
    switch (outputFlag) {
        case TraversalType::inorder:
            os<<print(os, p->left)<<p->element<<print(os,p->right);
            break;
        case TraversalType::preorder:
            os<<p->element<<print(os, p->left)<<print(os,p->right);
            break;
        case TraversalType::postorder:
            os<<print(os, p->left)<<print(os,p->right)<<p->element;
            break;
    }
}
template <class Object,class TreeNode>
void BinarySearchTree<Object,TreeNode>::destroy(TreeNode* p){
    if (p != nullptr){
        destroy(p->left);
        destroy(p->right);
        delete p;
    }
}
template <class Object,class TreeNode>
bool BinarySearchTree<Object,TreeNode>::contains(const Object& x, TreeNode* p) const{
    if (p == nullptr)
        return false;
    else if (x == p->element)
        return true;
    else if (x < p->element)
        return  contains(x,p->left);
    else
        return contains(x,p->right);
    return true;
}
template <class Object,class TreeNode>
TreeNode* BinarySearchTree<Object,TreeNode>::findMin(TreeNode* p) const{
    if (p->left == nullptr)
        return p;
    return findMin(p->left);
}
template <class Object,class TreeNode>
TreeNode* BinarySearchTree<Object,TreeNode>::findMax(TreeNode * p) const{
    if (p->right == nullptr)
        return p;
    return findMax(p->right);
}
template <class Object,class TreeNode>
TreeNode* BinarySearchTree<Object,TreeNode>::clone(TreeNode* rhst) {
    if (rhst == nullptr)
        return nullptr;
    return new TreeNode(rhst->element,clone(rhst->left),clone(rhst->right));
}
template <class Object>
const AVLSearchTree<Object> & AVLSearchTree<Object>::operator = (const AVLSearchTree & rhs){
    if (this != &rhs){
        this->clear();
        this->root = this->clone(rhs.root);
    }
    return *this;
}
template <class Object>
AVLTreeNode<Object>* AVLSearchTree<Object>::rightRotate(AVLTreeNode<Object>* y) {
    node* x = y->left;
    node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}
template <class Object>
AVLTreeNode<Object>*AVLSearchTree<Object>::leftRotate(AVLTreeNode<Object>* x) {
    node* y = x->right;
    node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
template <class Object>
AVLTreeNode<Object>* AVLSearchTree<Object>::clone(AVLTreeNode<Object>* rhst) const{
    if (rhst == nullptr)
        return nullptr;
    return new AVLTreeNode<Object>(rhst->element,rhst->height,clone(rhst->left),clone(rhst->right));
}
