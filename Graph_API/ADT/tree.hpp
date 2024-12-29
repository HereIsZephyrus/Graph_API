//
//  tree.hpp
//  data_structure
//
//  Created by ChanningTong on 10/21/24.
//

#ifndef tree_h
#define tree_h
#include <iostream>
#include <fstream>
#include <strstream>
#include <exception>
#include <vector>
#include <map>

namespace tcb {
using std::ostream;
enum class TraversalType{
    preorder,
    inorder,
    postorder
};
template<class Object>
struct TreeNode{
    Object element;
    TreeNode *firstChild;
    TreeNode *nextSibling;
    TreeNode(const Object& x, TreeNode* fchild = nullptr, TreeNode* sibling = nullptr):
    element(x),firstChild(fchild),nextSibling(sibling){}
};
template<class Object>
struct BinaryTreeNode{
    Object element;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode(const Object& x, BinaryTreeNode* lt = nullptr, BinaryTreeNode* rt = nullptr):
    element(x),left(lt),right(rt){}
};

template <class Object,class NodeStructure>
class Tree {
protected:
    //size_t size;
    NodeStructure* root;
public:
    Tree():root(nullptr){}
    ~Tree(){}
    bool isEmpty(){
        if (root == nullptr)
            return true;
        return false;
    }
    virtual void clear() = 0;
    virtual bool contains(const Object& x) const = 0;
    virtual void insert(const Object& x, NodeStructure* & node) = 0;
    virtual void remove(const Object& x, NodeStructure* & node) = 0;
};

template <class Object,class TreeNode = BinaryTreeNode<Object>>
class BinarySearchTree : protected Tree<Object, TreeNode>{
    using node = TreeNode;
    using BST = BinarySearchTree;
    static TraversalType outputFlag;
public:
    BinarySearchTree(){this->root = nullptr;}
    ~BinarySearchTree(){clear();}
    const BST & operator = (const BST & rhs){
        if (this != &rhs){
            clear();
            this->root = clone(rhs.root);
        }
        return *this;
    }
    BinarySearchTree(const BST & rhs) {
        if (this != &rhs){
            clear();
            this->root = clone(rhs.root);
        }
    }
    friend ostream& operator<<(ostream& os, const BST& tree);
    bool contains(const Object& x) const override{return contains(x, this->root);}
    void insert(const Object& x){insert(x, this->root);}
    void remove(const Object& x){remove(x, this->root);}
    void clear() override{destroy(this->root);}
    const Object& findMin() const{
        if (this -> root == nullptr)
            throw std::logic_error("the tree is empty");
        return findMin(this->root)->element;
    }
    const Object& findMax() const{
        if (this -> root == nullptr)
            throw std::logic_error("the tree is empty");
        return findMax(this->root)->element;
    }
    static ostream& preorder(ostream& os){
        outputFlag = TraversalType::preorder;
        return os;
    }
    static ostream& inorder(ostream& os){
        outputFlag = TraversalType::inorder;
        return os;
    }
    static ostream& postorder(ostream& os){
        outputFlag = TraversalType::postorder;
        return os;
    }
protected:
    static ostream& print(ostream& os, node* p){
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
    void destroy(node* p){
        if (p != nullptr){
            destroy(p->left);
            destroy(p->right);
            delete p;
        }
    }
    bool contains(const Object& x, node* p) const{
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
    node* findMin(node* p) const{
        if (p->left == nullptr)
            return p;
        return findMin(p->left);
    }
    node* findMax(node * p) const{
        if (p->right == nullptr)
            return p;
        return findMax(p->right);
    }
    node* clone(node* rhst) {
        if (rhst == nullptr)
            return nullptr;
        return new node(rhst->element,clone(rhst->left),clone(rhst->right));
    }
    void insert(const Object& x, node* & p) override{
        if ( p == nullptr)
            p  = new node(x, nullptr, nullptr);
        if (p->element == x)
            return;
        else if (x < p->element)
            insert(x, p->left);
        else
            insert(x, p->right);
    }
    void remove(const Object& x, node* & p) override{
        if (p == nullptr)
            return;
        if (x < p->element)
            remove(x, p->left);
        else if (x > p->element)
            remove(x, p->right);
        else{// find it
            if (p->left != nullptr && p->right != nullptr){
                p->element = findMin(p->right)->element;
                remove(p->element, p->right);
            }
            else{
                node* ret_p = p;
                if (p->left == nullptr)
                    p = p->right;
                else
                    p = p->left;
                delete ret_p;
            }
        }
    }
};
template <class Object,class TreeNode>
TraversalType BinarySearchTree<Object,TreeNode>::outputFlag = TraversalType::inorder;
template <class Object>
ostream& operator<<(ostream& os,const BinarySearchTree<Object>& tree){return BinarySearchTree<Object>::print(os,tree.root);}
template <class Object>
struct AVLTreeNode{
    int height;
    Object element;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode(const Object& x, int h, AVLTreeNode* lt = nullptr, AVLTreeNode* rt = nullptr):
    element(x),height(h),left(lt),right(rt){}
};
template <class Object>
class AVLSearchTree : public BinarySearchTree<Object,AVLTreeNode<Object>>{
    using AVL = AVLSearchTree;
    using node = AVLTreeNode<Object>;
public:
    AVLSearchTree(){this->root = nullptr;}
    ~AVLSearchTree(){}
    const AVL & operator = (const AVL & rhs){
        if (this != &rhs){
            this->clear();
            this->root = this->clone(rhs.root);
        }
        return *this;
    }
    void insert(const Object& x){insert(x, this->root);}
    void remove(const Object& x){remove(x, this->root);}
private:
    int getHeight(node* p) const {return (p != nullptr) ? p->height : 0;}
    int getBalance(node* p) const {return (p != nullptr) ?  0 : getHeight(p->left) - getHeight(p->right);}
    node* rightRotate(node* y) {
        node* x = y->left;
        node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
    node* leftRotate(node* x) {
        node* y = x->right;
        node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
protected:
    node* clone(node* rhst) const{
        if (rhst == nullptr)
            return nullptr;
        return new node(rhst->element,rhst->height,clone(rhst->left),clone(rhst->right));
    }
    void insert(const Object& x, node* & p){
        if ( p == nullptr)
            p  = new node(x, 1, nullptr, nullptr);
        if (p->element == x)
            return;
        else if (x < p->element)
            insert(x, p->left);
        else
            insert(x, p->right);
        p->height = 1 + std::max(getHeight(p->left),getHeight(p->right));
        int balance = getBalance(p);
        if (balance > 1 && x < p->left->element)
            p = rightRotate(p);
        else if (balance < -1 && x > p->right->element)
           p = leftRotate(p);
        else if (balance > 1 && x > p->left->element) {
            p->left = leftRotate(p->left);
            p = rightRotate(p);
       }
        else if (balance < -1 && x < p->right->element) {
            p->right = rightRotate(p->right);
           p = leftRotate(p);
       }
    }
    void remove(const Object& x, node* & p){
        if (p == nullptr)
            return;
        if (x < p->element)
            remove(x, p->left);
        else if (x > p->element)
            remove(x, p->right);
        else{// find it
            if (p->left != nullptr && p->right != nullptr){
                p->element = this->findMin(p->right)->element;
                remove(p->element, p->right);
            }
            else{
                node* ret_p = p;
                if (p->left == nullptr)
                    p = p->right;
                else
                    p = p->left;
                delete ret_p;
            }
        }
        if (this->root == nullptr)
            return;
        this->root->height = 1 + std::max(getHeight(this->root->left), getHeight(this->root->right));
        int balance = getBalance(this->root);
        if (balance > 1 && getBalance(this->root->left) >= 0)
            this->root = rightRotate(this->root);
        else if (balance < -1 && getBalance(this->root->right) <= 0)
            this->root = leftRotate(this->root);
        else if (balance > 1 && getBalance(this->root->left) < 0) {
            this->root->left = leftRotate(this->root->left);
            this->root = rightRotate(this->root);
        }
        else if (balance < -1 && getBalance(this->root->right) > 0) {
            this->root->right = rightRotate(this->root->right);
            this->root = leftRotate(this->root);
        }
    }
};
}
#endif /* tree_h */
