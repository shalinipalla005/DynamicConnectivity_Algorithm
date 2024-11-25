#include <bits/stdc++.h>
using namespace std;

#define RIGHT true
#define LEFT false

// Structure representing a node in the tree
struct TreeNode
{
    TreeNode *parent, *left, *right;
    int vert1, vert2;
    unsigned int size;

    // Constructor initializes the node with vertices and sets other pointers to nullptr
    TreeNode(int ver1_, int ver2_) : parent(nullptr), left(nullptr), right(nullptr), size(1), vert1(ver1_), vert2(ver2_) {}
};

// Class representing a Splay Forest
class SplayForest
{
private:
    // Updates the size of the node
    void updateSize(TreeNode *t)
    {
        t->size = (t->right ? t->right->size : 0) + (t->left ? t->left->size : 0) + 1;
    }

    // Performs a right rotation around the given node
    void rightRotate(TreeNode *n)
    {
        TreeNode *p = n->parent;
        TreeNode *gp = p->parent;

        // Updates grandparent's child pointer to the new rotated node
        if (gp)
        {
            (gp->right == p ? gp->right : gp->left) = n;
        }

        // Updates parent and child pointers for the rotation
        n->parent = gp;
        p->parent = n;
        p->left = n->right;

        if (p->left)
        {
            p->left->parent = p;
        }

        n->right = p;
        updateSize(p);
        updateSize(n);
    }

    // Performs a left rotation around the given node
    void leftRotate(TreeNode *n)
    {
        TreeNode *p = n->parent;
        TreeNode *gp = p->parent;

        // Updates grandparent's child pointer to the new rotated node
        if (gp)
        {
            (gp->right == p ? gp->right : gp->left) = n;
        }

        // Updates parent and child pointers for the rotation
        n->parent = gp;
        p->parent = n;
        p->right = n->left;

        if (p->right)
        {
            p->right->parent = p;
        }

        n->left = p;
        updateSize(p);
        updateSize(n);
    }

    // Splays the given node to the root
    void splay(TreeNode *n)
    {
        while (n->parent)
        {
            TreeNode *p = n->parent;
            TreeNode *gp = p->parent;

            if (!gp)
            {
                // No grandparent, perform a single rotation
                (n == p->left) ? rightRotate(n) : leftRotate(n);
                break;
            }

            if (n == p->left)
            {
                if (p == gp->left)
                {
                    // zig-zig
                    rightRotate(p);
                }
                else
                {
                    // zig-zag
                    rightRotate(n);
                    leftRotate(n);
                }
            }
            else
            {
                if (p == gp->left)
                {
                    // zag-zig
                    leftRotate(n);
                    rightRotate(n);
                }
                else
                {
                    // zag-zag
                    leftRotate(p);
                    leftRotate(n); // Common part for zig-zig and zag-zag
                }
            }
            
        }
    }

public:
    // Default constructor
    SplayForest() {}

    // Creates a new node with the given vertices
    TreeNode *insertNode(int u, int v)
    {
        TreeNode *p = new TreeNode(u, v);
        if (!p)
        {
            cerr << "Memory allocation failed" << endl;
            exit(1);
        }
        return p;
    }

    // Finds the next node in an inorder traversal
    TreeNode *getNext(TreeNode *t)
    {
        if (!t)
            return nullptr;

        if (t->right)
            return findLeftMost(t->right);

        TreeNode *parent = t->parent;
        while (parent)
        {
            if (t == parent->left)
                return parent;
            t = parent;
            parent = t->parent;
        }

        return nullptr;
    }

    // Performs an inorder traversal of the tree
    void inorder(TreeNode *t)
    {
        if (t == nullptr)
            return;

        inorder(t->left);
        cout << t->vert1 + 1;
        inorder(t->right);
    }

    // Splits the tree at the given node, either to the right or left
    TreeNode *split(TreeNode *t, bool right)
    {
        if (!t)
            return t;

        splay(t);
        if (right)
        {
            if (!t->right)
                return nullptr;

            TreeNode *temp = t->right;
            t->right = temp->parent = nullptr;
            t->size -= temp->size;
            return temp;
        }
        else
        {
            if (!t->left)
                return nullptr;

            TreeNode *temp = t->left;
            t->left = temp->parent = nullptr;
            t->size -= temp->size;
            return temp;
        }
    }

    // Merges two trees into a single tree
    TreeNode *merge(TreeNode *t1, TreeNode *t2)
    {
        if (!t1 || !t2)
            return (t1 == nullptr) ? t2 : t1;

        t1 = findRightMost(findBSTRoot(t1));
        t2 = findBSTRoot(t2);
        splay(t1);

        t1->right = t2;
        t2->parent = t1;

        t1->size += t2->size;

        return t1;
    }

    // Finds the root of the BST containing the given node
    TreeNode *findBSTRoot(TreeNode *t)
    {
        if (!t)
            return nullptr;

        while (t->parent)
            t = t->parent;
        return t;
    }

    // Finds the rightmost node in the tree
    TreeNode *findRightMost(TreeNode *t1)
    {
        if (!t1)
            return nullptr;

        while (t1->right)
            t1 = t1->right;
        return t1;
    }

    // Finds the leftmost node in the tree
    TreeNode *findLeftMost(TreeNode *t)
    {
        if (!t)
            return nullptr;

        while (t->left)
            t = t->left;
        return t;
    }
};
