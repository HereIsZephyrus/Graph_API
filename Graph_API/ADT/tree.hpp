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
    //virtual void insert(const Object& x, NodeStructure* & node) = 0; node structure overload problem
    //virtual void remove(const Object& x, NodeStructure* & node) = 0;
};

template <class Object,class TreeNode = BinaryTreeNode<Object>>
class BinarySearchTree : protected Tree<Object, TreeNode>{
    using node = TreeNode;
    using BST = BinarySearchTree;
    static TraversalType outputFlag;
public:
    BinarySearchTree(){this->root = nullptr;}
    ~BinarySearchTree(){clear();}
    const BST & operator = (const BST & rhs);
    BinarySearchTree(const BST & rhs);
    friend ostream& operator<<(ostream& os, const BST& tree);
    virtual bool contains(const Object& x) const override{return contains(x, this->root);}
    virtual void insert(const Object& x){insert(x, this->root);}
    virtual void remove(const Object& x){remove(x, this->root);}
    void clear() override{destroy(this->root);}
    const Object& findMin() const;
    const Object& findMax() const;
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
    static ostream& print(ostream& os, node* p);
    void destroy(node* p);
    bool contains(const Object& x, node* p) const;
    node* findMin(node* p) const;
    node* findMax(node * p) const;
    virtual node* clone(node* rhst);
    virtual void insert(const Object& x, node* & p){
        if ( p == nullptr)
            p  = new node(x, nullptr, nullptr);
        if (p->element == x)
            return;
        else if (x < p->element)
            insert(x, p->left);
        else
            insert(x, p->right);
    }
    virtual void remove(const Object& x, node* & p){
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
protected:
    node* clone(node* rhst) override;
    void insert(const Object& x, node* & p) override{
        if ( p == nullptr)
            p  = new node(x, nullptr, nullptr, 1);
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
    void remove(const Object& x, node* & p) override{
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
    Vector<Point> points;
    QuadTreeNode* northeast;
    QuadTreeNode* northwest;
    QuadTreeNode* southeast;
    QuadTreeNode* southwest;
    int capacity;
    bool isLeaf;
    SpatialRange range;
    QuadTreeNode(SpatialRange r,int c,QuadTreeNode* ne = nullptr, QuadTreeNode* nw = nullptr,QuadTreeNode* se = nullptr, QuadTreeNode* sw = nullptr):
    range(r),capacity(c),northeast(ne),northwest(nw),southeast(se),southwest(sw){
        points.clear();
        if (ne != nullptr || nw != nullptr || se != nullptr || sw != nullptr)
            isLeaf = false;
        else
            isLeaf = true;
    }
};
template <class Object>
class QuadTree : protected Tree<Object, QuadTreeNode<Object>>{
    using node = QuadTreeNode<Object>;
    using insertRes = std::pair<bool,node*>;
public:
    QuadTree(){this->root = nullptr;}
    QuadTree(const SpatialRange& r, int c){this->root = new node(r,c);}
    const QuadTree & operator = (const QuadTree & rhs){
        if (this != &rhs){
            clear();
            this->root = clone(rhs.root);
        }
        return *this;
    }
    ~QuadTree(){clear();}
    void clear(){destroy(this->root);}
    node* insert(GLfloat x,GLfloat y,const Object& obj){return insert(x,y,obj,this->root).second;};
    Vector<Object> queryRange(const SpatialRange& orientRange){return queryRange(orientRange,this->root);}
private:
    void destroy(node* p){
        if (p != nullptr){
            destroy(p->northeast);
            destroy(p->northwest);
            destroy(p->southeast);
            destroy(p->southwest);
            delete p;
        }
    }
    node* clone(node* rhst) const{
        if (rhst == nullptr)
            return nullptr;
        return new node(rhst->range,rhst->capacity,clone(rhst->northeast),clone(rhst->northwest),clone(rhst->southeast),clone(rhst->southwest));
    }
    void subdivide(node *p) {
        SpatialRange& range = p->range;
        p->northeast = new node(SpatialRange(range.minx + range.width / 2, range.miny, range.width / 2, range.height / 2), p->capacity);
        p->northwest = new node(SpatialRange(range.minx, range.miny, range.width / 2, range.height / 2), p->capacity);
        p->southeast = new node(SpatialRange(range.minx + range.width / 2, range.miny + range.height / 2, range.width / 2, range.height / 2), p->capacity);
        p->southwest = new node(SpatialRange(range.minx, range.miny + range.height / 2, range.width / 2, range.height / 2), p->capacity);
        p->isLeaf = false;
    }
    insertRes insert(GLfloat x,GLfloat y,const Object& obj,node *p){
        const SpatialRange& range = p->range;
        bool contain = (x >= range.minx && x < range.minx + range.width && y >= range.miny && y < range.miny + range.height);
        if (!contain) return std::make_pair(false, nullptr);
        if (p->points.size() < p->capacity) {
            p->points.push_back(Point(x,y,obj));
            return std::make_pair(true, p);
        }
        if (p->isLeaf)            subdivide(p);
        insertRes ret_res = insert(x,y,obj,p->northeast);
        if (ret_res.first) return ret_res;
        ret_res = insert(x,y,obj,p->northwest);
        if (ret_res.first) return ret_res;
        ret_res = insert(x,y,obj,p->southeast);
        if (ret_res.first) return ret_res;
        ret_res = insert(x,y,obj,p->southwest);
        if (ret_res.first) return ret_res;
        return std::make_pair(false, nullptr);
    }
    Vector<Object> queryRange(const SpatialRange& orientRange,node *p) {
        Vector<Object> foundPoints;
        const SpatialRange& range = p->range;
        bool intersect = !(orientRange.minx > range.minx + range.width || orientRange.minx + orientRange.width < range.minx || orientRange.miny > range.miny + range.height || orientRange.miny + orientRange.height < range.miny);
        if (!intersect) return foundPoints;

        for (size_t i = 0; i < p->points.size(); i++) {
            const GLfloat px = p->points[i].x, py = p->points[i].y;
            if (px >= orientRange.minx && px < orientRange.minx + orientRange.width && py >= orientRange.miny && py < orientRange.miny + orientRange.height) {
                foundPoints.push_back(p->points[i].element);
            }
        }
        if (!p->isLeaf) {
            Vector<Object> northeastPoints = queryRange(orientRange,p->northeast);
            Vector<Object> northwestPoints = queryRange(orientRange,p->northwest);
            Vector<Object> southeastPoints = queryRange(orientRange,p->southeast);
            Vector<Object> southwestPoints = queryRange(orientRange,p->southwest);
            foundPoints.insert(foundPoints.end(), northeastPoints.begin(), northeastPoints.end());
            foundPoints.insert(foundPoints.end(), northwestPoints.begin(), northwestPoints.end());
            foundPoints.insert(foundPoints.end(), southeastPoints.begin(), southeastPoints.end());
            foundPoints.insert(foundPoints.end(), southwestPoints.begin(), southwestPoints.end());
        }

        return foundPoints;
    }
};
}
#include "tree.tpp"
#endif /* tree_h */
