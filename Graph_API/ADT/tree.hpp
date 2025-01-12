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
#include "linear.hpp"

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
};
template <class Object,class NodeStructure>
class SearchTree : public Tree<Object, NodeStructure>{
protected:
    static TraversalType outputFlag;
    static ostream& print(ostream& os, NodeStructure* p);
public:
    SearchTree():Tree<Object, NodeStructure>(){}
    ~SearchTree(){}
    bool isEmpty(){
        if (this->root == nullptr)
            return true;
        return false;
    }
    virtual bool contains(const Object& x) const = 0;
    virtual void insert(const Object& x, NodeStructure* & node) = 0;
    virtual void remove(const Object& x, NodeStructure* & node) = 0;
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
};

template <class Object,class TreeNode = BinaryTreeNode<Object>>
class BinarySearchTree : protected SearchTree<Object, TreeNode>{
    using node = TreeNode;
    using BST = BinarySearchTree;
public:
    BinarySearchTree(){this->root = nullptr;}
    ~BinarySearchTree(){clear();}
    const BST & operator = (const BST & rhs);
    BinarySearchTree(const BST & rhs);
    friend ostream& operator<<(ostream& os, const BST& tree);
    bool contains(const Object& x) const override {return contains(x, this->root);}
    virtual void insert(const Object& x){insert(x, this->root);}
    virtual void remove(const Object& x){remove(x, this->root);}
    void clear() override{destroy(this->root);}
    const Object& findMin() const;
    const Object& findMax() const;
private:
    void insert(const Object& x, node* & p) override;
    void remove(const Object& x, node* & p) override;
    node* clone(node* rhst);
protected:
    void destroy(node* p);
    bool contains(const Object& x, node* p) const;
    node* findMin(node* p) const;
    node* findMax(node * p) const;
};
template <class Object,class TreeNode>
TraversalType SearchTree<Object,TreeNode>::outputFlag = TraversalType::inorder;
template <class Object>
ostream& operator<<(ostream& os,const BinarySearchTree<Object>& tree){return BinarySearchTree<Object>::print(os,tree.root);}
template <class Object>
struct AVLTreeNode{
    int height;
    Object element;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode(const Object& x, AVLTreeNode* lt = nullptr, AVLTreeNode* rt = nullptr, int h = 1):
    element(x),height(h),left(lt),right(rt){}
    AVLTreeNode(AVLTreeNode* rhs)
    : element(rhs->element), height(rhs->height),
      left(rhs->left ? new AVLTreeNode(*rhs->left) : nullptr),
      right(rhs->right ? new AVLTreeNode(*rhs->right) : nullptr) {}
};
template <class Object>
class AVLSearchTree : public BinarySearchTree<Object,AVLTreeNode<Object>>{
    using AVL = AVLSearchTree;
    using node = AVLTreeNode<Object>;
public:
    AVLSearchTree(){this->root = nullptr;}
    ~AVLSearchTree(){}
    const AVL & operator = (const AVL & rhs);
    void insert(const Object& x) override{insert(x, this->root);}
    void remove(const Object& x) override{remove(x, this->root);}
private:
    int getHeight(node* p) const {return (p != nullptr) ? p->height : 0;}
    int getBalance(node* p) const {return (p != nullptr) ?  0 : getHeight(p->left) - getHeight(p->right);}
    node* rightRotate(node* y);
    node* leftRotate(node* x);
    node* clone(node* rhst);
    void insert(const Object& x, node* & p) override;
    void remove(const Object& x, node* & p) override;
};
struct SpatialRange{
    float minx,miny,width,height;
    SpatialRange(float x, float y, float w, float h):minx(x),miny(y),width(w),height(h){}
};
template<class Object>
struct QuadTreeNode{
    struct Point{
        float x,y;
        Object element;
        Point(float x, float y, const Object& obj):x(x),y(y),element(obj){}
    };
    std::vector<Point> points;
    QuadTreeNode* northeast;
    QuadTreeNode* northwest;
    QuadTreeNode* southeast;
    QuadTreeNode* southwest;
    int capacity;
    bool isLeaf;
    SpatialRange range;
    QuadTreeNode(SpatialRange r,int c,QuadTreeNode* ne = nullptr, QuadTreeNode* nw = nullptr,QuadTreeNode* se = nullptr, QuadTreeNode* sw = nullptr);
};
template <class Object>
class QuadTree : protected Tree<Object, QuadTreeNode<Object>>{
    using node = QuadTreeNode<Object>;
    using insertRes = std::pair<bool,node*>;
    using Point = node::Point;
public:
    QuadTree(){this->root = nullptr;}
    QuadTree(const SpatialRange& r, int c){this->root = new node(r,c);}
    const QuadTree & operator = (const QuadTree & rhs);
    ~QuadTree(){clear();}
    void clear(){destroy(this->root);}
    void insert(float x,float y,const Object& obj){ insert(x,y,obj,this->root);}
    void remove(float x,float y){remove(x,y,this->root);}
    std::vector<Object> queryRange(const SpatialRange& orientRange){return queryRange(orientRange,this->root);}
private:
    void destroy(node* p);
    node* clone(node* rhst) const;
    void subdivide(node *p);
    insertRes insert(float x,float y,const Object& obj,node *p);
    void remove(float x,float y,node *p);
    std::vector<Object> queryRange(const SpatialRange& orientRange,node *p);
};
}
#include "tree.tpp"
#endif /* tree_h */
