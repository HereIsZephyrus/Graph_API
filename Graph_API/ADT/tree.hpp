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
struct SpatialRange{
    float minx,miny,width,height;
    SpatialRange(float x, float y, float w, float h):minx(x),miny(y),width(w),height(h){}
};
template<class Object>
struct Point{
    float x,y;
    Object element;
    Point(float x, float y, const Object& obj):x(x),y(y),element(obj){}
};
template<class Object>
struct QuadTreeNode{
    std::vector<Point<Object>> points;
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

template <class Object,class NodeStructure>
class Tree {
protected:
    //size_t size;
    NodeStructure* root;
public:
    Tree(){}
    ~Tree(){}
    bool isEmpty(){
        if (root == nullptr)
            return true;
        return false;
    }
    virtual void clear() = 0;
    //virtual bool contains(const Object& x) const;
    //virtual void insert(const Object& x, NodeStructure* & node) const;
    //virtual void remove(const Object& x, NodeStructure* & node) const;
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
    friend ostream& operator<<(ostream& os, const BST& tree);
    bool contains(const Object& x) const{return contains(x, this->root);}
    void insert(const Object& x){insert(x, this->root);}
    void remove(const Object& x){remove(x, this->root);}
    void clear() {destroy(this->root);}
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
    void insert(const Object& x, node* & p){
        if ( p == nullptr)
            p  = new node(x, nullptr, nullptr);
        if (p->element == x)
            return;
        else if (x < p->element)
            insert(x, p->left);
        else
            insert(x, p->right);
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
enum RBColor { RED, BLACK };
template<class Object>
struct RBTreeNode{
    RBColor color;
    Object element;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parrent;
    RBTreeNode(const Object& x, RBColor c = RED, RBTreeNode* lt = nullptr, RBTreeNode* rt = nullptr, RBTreeNode *p = nullptr):
    element(x),color(c),left(lt),right(rt),parrent((p)){}
};
template <class Object>
class RBSearchTree : public BinarySearchTree<Object,RBTreeNode<Object>>{
    using RB = RBSearchTree;
    using node = RBTreeNode<Object>;
public:
    RBSearchTree(){this->root = nullptr;}
    ~RBSearchTree(){}
    const RB & operator = (const RB & rhs){
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
    void fixInsert(node *p) {
        while (p != this->root && p->parent->color == RED) {
            if (p->parent == p->parent->parent->left) {
                node* uncle = p->parent->parent->right;
                if (uncle && uncle->color == RED) {
                    // Case 1: Uncle is RED
                    p->parent->color = BLACK;
                    p->color = BLACK;
                    p->parent->parent->color = RED;
                    p = p->parent->parent;
                } else {
                    if (p == p->parent->right) {
                        // Case 2: Node is right child
                        p = p->parent;
                        rotateLeft(p);
                    }
                    // Case 3: Node is left child
                    p->parent->color = BLACK;
                    p->parent->parent->color = RED;
                    rotateRight(p->parent->parent);
                }
            } else {
                // Mirror case for the right child
                // ...
            }
        }
        this->root->color = BLACK;
    }
protected:
    node* clone(node* rhst) const{
        if (rhst == nullptr)
            return nullptr;
        return new node(rhst->element,rhst->color,clone(rhst->left),clone(rhst->right),rhst->parrent);
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
    node* insert(float x,float y,const Object& obj){return insert(x,y,obj,this->root).second;};
    std::vector<Object> queryRange(const SpatialRange& orientRange){return queryRange(orientRange,this->root);}
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
    insertRes insert(float x,float y,const Object& obj,node *p){
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
    std::vector<Object> queryRange(const SpatialRange& orientRange,node *p) {
        std::vector<Object> foundPoints;
        const SpatialRange& range = p->range;
        bool intersect = !(orientRange.minx > range.minx + range.width || orientRange.minx + orientRange.width < range.minx || orientRange.miny > range.miny + range.height || orientRange.miny + orientRange.height < range.miny);
        if (!intersect) return foundPoints;

        for (size_t i = 0; i < p->points.size(); i++) {
            const float px = p->points[i].x, py = p->points[i].y;
            if (px >= orientRange.minx && px < orientRange.minx + orientRange.width && py >= orientRange.miny && py < orientRange.miny + orientRange.height) {
                foundPoints.push_back(p->points[i].element);
            }
        }
        if (!p->isLeaf) {
            std::vector<Object> northeastPoints = queryRange(orientRange,p->northeast);
            std::vector<Object> northwestPoints = queryRange(orientRange,p->northwest);
            std::vector<Object> southeastPoints = queryRange(orientRange,p->southeast);
            std::vector<Object> southwestPoints = queryRange(orientRange,p->southwest);
            foundPoints.insert(foundPoints.end(), northeastPoints.begin(), northeastPoints.end());
            foundPoints.insert(foundPoints.end(), northwestPoints.begin(), northwestPoints.end());
            foundPoints.insert(foundPoints.end(), southeastPoints.begin(), southeastPoints.end());
            foundPoints.insert(foundPoints.end(), southwestPoints.begin(), southwestPoints.end());
        }

        return foundPoints;
    }
};
}
#endif /* tree_h */
