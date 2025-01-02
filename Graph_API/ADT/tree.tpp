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
ostream& BinarySearchTree<Object,TreeNode>::print(ostream& os, TreeNode* p){
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
    return new node(rhst->element,clone(rhst->left),clone(rhst->right));
}
template <class Object>
const AVLSearchTree<Object> & AVLSearchTree<Object>::operator = (const AVLSearchTree & rhs){
    if (this != &rhs){
        this->clear();
        this->root = clone(rhs.root);
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
AVLTreeNode<Object>* AVLSearchTree<Object>::clone(AVLTreeNode<Object>* rhst){
    if (rhst == nullptr)
        return nullptr;
    return new node(rhst);
}
template <class Object>
QuadTreeNode<Object>::QuadTreeNode(SpatialRange r,int c,QuadTreeNode* ne, QuadTreeNode* nw,QuadTreeNode* se, QuadTreeNode* sw):
range(r),capacity(c),northeast(ne),northwest(nw),southeast(se),southwest(sw){
    points.clear();
    if (ne != nullptr || nw != nullptr || se != nullptr || sw != nullptr)
        isLeaf = false;
    else
        isLeaf = true;
}
template <class Object>
const QuadTree<Object> & QuadTree<Object>::operator = (const QuadTree & rhs){
    if (this != &rhs){
        clear();
        this->root = clone(rhs.root);
    }
    return *this;
}
template <class Object>
void QuadTree<Object>::destroy(node* p){
    if (p != nullptr){
        destroy(p->northeast);
        destroy(p->northwest);
        destroy(p->southeast);
        destroy(p->southwest);
        delete p;
    }
}
template <class Object>
QuadTreeNode<Object>* QuadTree<Object>::clone(QuadTreeNode<Object>* rhst) const{
    if (rhst == nullptr)
        return nullptr;
    return new node(rhst->range,rhst->capacity,clone(rhst->northeast),clone(rhst->northwest),clone(rhst->southeast),clone(rhst->southwest));
}
template <class Object>
void QuadTree<Object>::subdivide(QuadTreeNode<Object> *p) {
    SpatialRange& range = p->range;
    p->northeast = new QuadTreeNode<Object>(SpatialRange(range.minx + range.width / 2, range.miny, range.width / 2, range.height / 2), p->capacity);
    p->northwest = new QuadTreeNode<Object>(SpatialRange(range.minx, range.miny, range.width / 2, range.height / 2), p->capacity);
    p->southeast = new QuadTreeNode<Object>(SpatialRange(range.minx + range.width / 2, range.miny + range.height / 2, range.width / 2, range.height / 2), p->capacity);
    p->southwest = new QuadTreeNode<Object>(SpatialRange(range.minx, range.miny + range.height / 2, range.width / 2, range.height / 2), p->capacity);
    p->isLeaf = false;
}
template <class Object>
    std::pair<bool,QuadTreeNode<Object>*> QuadTree<Object>::insert(float x,float y,const Object& obj,QuadTreeNode<Object> *p){
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
template <class Object>
std::vector<Object> QuadTree<Object>::queryRange(const SpatialRange& orientRange,node *p) {
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
