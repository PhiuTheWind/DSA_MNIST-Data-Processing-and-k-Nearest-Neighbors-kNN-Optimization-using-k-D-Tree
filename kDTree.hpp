#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */



struct kDTreeNode
{
    vector<int> data;
    int label;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = 0;
        this->left = left;
        this->right = right;
    }
    kDTreeNode(vector<int> data, int label, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = label;
        this->left = nullptr;
        this->right = nullptr;
    }
    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }
};

class kDTree
{
private:
    int k;  
    kDTreeNode *root;
    int counting;

public:
    kDTree(int k = 2);
    ~kDTree();
    int getK() const 
    {
        return k;
    }
    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    int height() const;
    int nodeCount() const;
    int leafCount () const;

    void insert(const vector<int>& point);
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode *&best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList);
    void buildTreeLable(const vector<vector<int>> &pointList, const vector<int> &label);
    
    //My functions:
    friend class kNN;
    kDTreeNode* copyTraversal(const kDTreeNode * temp);
    void re_inorderTraversal(kDTreeNode * node_tree) const;
    void re_preorderTraversal(kDTreeNode * node_tree) const;
    void re_postorderTraversal(kDTreeNode* node) const;
    int re_height (kDTreeNode * cur_node) const;
    int leafCountRec(kDTreeNode *node) const;
    kDTreeNode* recInsert(kDTreeNode * node, const vector<int> &points, int level);
    kDTreeNode *findMin(kDTreeNode *crnNode, int dim, int cdim);
    bool rec_seacch(kDTreeNode *temp, const vector<int> &point, int level);
    kDTreeNode* rec_remove(kDTreeNode * node, const vector<int> &point, int level);
    kDTreeNode * rec_buildTree(const vector<vector<int>> &pointList, int level);
    double squaredEuclideanDistance(const vector<int> &a, const vector<int> &b);
    void rec_nearestNeighbour(kDTreeNode *temp, const vector<int> &target, kDTreeNode *&best, int level);
    void rec_kNearestNeighbour(kDTreeNode *temp, const vector<int> &target, int k, vector<kDTreeNode *> &bestList, int level);
    kDTreeNode * buildTreeLableRec(const vector<vector<int>> &pointList, const vector<int> &label, int level);
    
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    kDTree training;
public:
    kNN(int k = 5):k(k){}
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
};

// Please add more or modify as needed
