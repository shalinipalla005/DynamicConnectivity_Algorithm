#include <bits/stdc++.h>
#include "SplayForest1.cpp"
using namespace std;

class SpanningForest
{
private:
    // Structure representing a node in the tree
    struct node_mp
    {
        TreeNode *aE;
        node_mp() : aE(nullptr) {}
    };

    SplayForest tree;     // SplayForest instance to manage the tree operations
    vector<node_mp> nodes; // Vector to store nodes with arbitrary edges

public:
    // Structure representing an edge in the spanning forest
    struct edge_map
    {
        TreeNode *o_1;
        TreeNode *o_2;

        edge_map(TreeNode *one, TreeNode *two) : o_1(one), o_2(two) {}
        edge_map() : o_1(nullptr), o_2(nullptr) {}
    };

    map<pair<int, int>, edge_map> edgeMap; // Map to store edges based on vertices

    // Constructor to initialize the vector of nodes
    SpanningForest(int n)
    {
        nodes.resize(n);

        for (auto &node : nodes)
        {
            node.aE = nullptr;
        }
    }

    // Print the arbitrary edges for each node
    void print()
    {
        for (const auto &node : nodes)
        {
            tree.inorder(tree.findBSTRoot(node.aE));
            cout << ", ";
        }
        cout << endl;
    }

    // Get the vertices in the connected component containing u
    vector<int> list_vert(int u)
    {
        TreeNode *root = nodes[u].aE;

        // Preliminary checks
        if (root == nullptr)
            return {u};

        vector<int> vertices;
        root = tree.findBSTRoot(root);
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();

            vertices.push_back((nodes[current->vert1].aE == current) ? current->vert1 : current->vert2);

            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }

        return vertices;
    }

    // Check if two vertices u and v are connected in the spanning forest
    bool connected(int u, int v)
    {
        TreeNode *edgeU = nodes[u].aE;
        TreeNode *edgeV = nodes[v].aE;

        if (edgeU == nullptr || edgeV == nullptr)
            return false;

        return tree.findBSTRoot(edgeU) == tree.findBSTRoot(edgeV);
    }

    // Check if an edge between u and v is present in the spanning forest
    bool isPresent(int u_, int v_)
    {
        int u = min(u_, v_), v = max(u_, v_);
        return edgeMap.count({u, v}) > 0;
    }

    // Check if node1 comes before node2 in the inorder traversal
    bool isBefore(TreeNode *node1, TreeNode *node2)
    {
        TreeNode *left = tree.split(node1, LEFT);

        if (tree.findBSTRoot(node1) == tree.findBSTRoot(node2))
        {
            tree.merge(left, node1);
            return true;
        }
        else
        {
            tree.merge(left, node1);
            return false;
        }
    }

    // Make a node with vertex v the root of its connected component
    TreeNode *makeRoot(int v)
    {
        if (nodes[v].aE == nullptr)
            return nullptr;

        TreeNode *aE = nodes[v].aE;
        int u_ = aE->vert1, v_ = aE->vert2;
        edge_map data = edgeMap[{min(u_, v_), max(u_, v_)}];

        TreeNode *splitEdge = (data.o_1->vert1 == v) ? data.o_1 : data.o_2;

        TreeNode *left = tree.split(splitEdge, LEFT);
        return tree.merge(splitEdge, left);
    }

    // Add an edge between u and v to the spanning forest
    void edge_addition(int u_, int v_)
    {
        int u = min(u_, v_), v = max(u_, v_);

        if (isPresent(u, v) || connected(u, v))
            return;

        edge_map &data = edgeMap[{u, v}];
        TreeNode *newNode1 = tree.insertNode(u, v);
        TreeNode *newNode2 = tree.insertNode(v, u);
        data = edge_map(newNode1, newNode2);

        TreeNode *left = makeRoot(u);
        TreeNode *right = makeRoot(v);
        left = tree.merge(left, newNode1);
        left = tree.merge(left, right);
        left = tree.merge(left, newNode2);

        nodes[u].aE = newNode1;
        nodes[v].aE = newNode2;
    }

    // Delete the edge between u and v from the spanning forest
    void edge_deletion(int u_, int v_)
    {
        int u = min(u_, v_), v = max(u_, v_);

        if (!isPresent(u, v))
            return;

        edge_map &data = edgeMap[{u, v}];
        TreeNode *first = data.o_1;
        TreeNode *last = data.o_2;

        edgeMap.erase({u, v});

        u = first->vert1;
        v = first->vert2;

        TreeNode *left = tree.split(first, LEFT);
        TreeNode *right = tree.split(last, RIGHT);
        TreeNode *repl1 = tree.findLeftMost(right);
        TreeNode *repl2 = tree.findRightMost(left);

        TreeNode *middle;
        middle = tree.split(last, LEFT);
        middle = tree.split(first, RIGHT);
        tree.merge(left, right);

        if (nodes[u].aE == first || nodes[u].aE == last)
        {
            nodes[u].aE = nullptr;
            nodes[u].aE = (repl1 != nullptr) ? repl1 : repl2;
        }

        if (nodes[v].aE == first || nodes[v].aE == last)
        {
            nodes[v].aE = tree.findLeftMost(middle);
        }

        delete first;
        delete last;
    }

    // Get the size of the connected component containing vertex u
    int getSize(int u)
    {
        TreeNode *root = nodes[u].aE;

        if (root == nullptr)
            return 1;

        TreeNode *bstRoot = tree.findBSTRoot(root);
        return bstRoot->size;
    }
};

