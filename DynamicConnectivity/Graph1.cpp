#include <bits/stdc++.h>
#include <sstream>
#include "SpanningForest1.cpp"
using namespace std;

#define printbool 0

class Graph
{
private:
    int vt;
    int logn;
    vector<SpanningForest> F;
    map<pair<int, int>, int> edge;        // Maps edges to the level in the Forest
    vector<vector<set<int>>> TE;    // Tree edges at each level
    vector<vector<set<int>>> NTE; // Non-tree edges at each level

    // Check if the given edge is a tree edge at the specified level
    bool check_TE(int u_, int v_, int level)
    {
        int u = min(u_, v_), v = max(u_, v_);
        return TE[level][u].find(v) != TE[level][u].end();
    }

public:
    Graph() {}

    // Print the state of the graph, including tree and non-tree edges
    void state_output()
    {
        stringstream result;

        for (int i = logn; i >= 0; i--)
        {
            result << i << "T ";
            for (int u = 0; u < vt; u++)
            {
                for (auto v : TE[i][u])
                {
                    if (u < v)
                        result << "(" << u + 1 << ", " << v + 1 << "); ";
                }
            }
            result << endl
                   << i << "NT ";
            for (int u = 0; u < vt; u++)
            {
                for (auto v : NTE[i][u])
                {
                    if (u < v)
                        result << "(" << u + 1 << ", " << v + 1 << "); ";
                }
            }
            result << endl;
        }

        cout << result.str() << endl;
    }

    // Constructor to initialize the graph with n vt
    Graph(int n)
    {
        vt = n;
        logn = static_cast<int>(log2(n));
        F.resize(logn + 1, SpanningForest(n));
        TE.resize(logn + 1, vector<set<int>>(n));
        NTE.resize(logn + 1, vector<set<int>>(n));
    }

    // Check if two vt are connected at the highest level of the F
    bool isConnected(int u_, int v_)
    {
        bool connected = F[logn].connected(u_, v_);

        if (printbool)
        {
            cout << "(" << u_ + 1 << ", " << v_ + 1 << ")";
            cout << (connected ? " is connected" : " is not connected") << endl;
        }

        return connected;
    }

    // Insert an edge into the graph
    void edge_insertion(int u_, int v_)
    {
        int u = min(u_, v_), v = max(u_, v_);

        if (v > vt || u < 0 || edge[{u, v}] != 0)
            return;

        edge[{u, v}] = logn;

        if (!F[logn].connected(u, v))
        {
            TE[logn][u].insert(v);
            TE[logn][v].insert(u);
            F[logn].edge_addition(u, v);
        }
        else
        {
            NTE[logn][u].insert(v);
            NTE[logn][v].insert(u);
        }

        if (printbool)
        {
            state_output();
        }
    }

    // Remove an edge from the graph
    void edge_removal(int u_, int v_)
    {
        int u = min(u_, v_), v = max(u_, v_);

        if (v > vt || u < 0)
            return;

        int level = edge[{u, v}];
        edge.erase({u, v});

        if (check_TE(u, v, level))
        {
            // Handle removal of a tree edge
            TE[level][u].erase(v);
            TE[level][v].erase(u);

            for (int i = level; i <= logn; i++)
                F[i].edge_deletion(u, v);

            for (int i = level; i <= logn; i++)
            {
                if (F[i].getSize(u) < F[i].getSize(v))
                    swap(u, v);

                vector<int> smallTree = F[i].list_vert(v);
                for (auto v1 : smallTree)
                {
                    vector<int> Del;
                    for (auto v2 : TE[i][v1])
                    {
                        Del.push_back(v2);
                        F[i - 1].edge_addition(v1, v2);
                        TE[i - 1][v1].insert(v2);
                        TE[i - 1][v2].insert(v1);
                        edge[{min(v1, v2), max(v2, v1)}] = i - 1;
                    }
                    for (auto v2 : Del)
                    {
                        TE[i][v2].erase(v1);
                        TE[i][v1].erase(v2);
                    }
                }

                bool bool_RE = false;
                for (auto v1 : smallTree)
                {
                    vector<int> Del;
                    for (auto v2 : NTE[i][v1])
                    {
                        Del.push_back(v2);
                        if (F[i].connected(v1, v2))
                        {
                            NTE[i - 1][v1].insert(v2);
                            NTE[i - 1][v2].insert(v1);
                            edge[{min(v1, v2), max(v2, v1)}] = i - 1;
                        }
                        else
                        {
                            bool_RE = true;
                            TE[i][v1].insert(v2);
                            TE[i][v2].insert(v1);

                            for (int j = i; j <= logn; j++)
                            {
                                F[j].edge_addition(v1, v2);
                            }
                            break;
                        }
                    }
                    for (auto v2 : Del)
                    {
                        NTE[i][v1].erase(v2);
                        NTE[i][v2].erase(v1);
                    }
                    if (bool_RE)
                        break;
                }
                if (bool_RE)
                    break;
            }
        }
        else
        {
            // Handle removal of a non-tree edge
            NTE[level][u].erase(v);
            NTE[level][v].erase(u);
        }

        if (printbool)
        {
            state_output();
        }
    }
};
