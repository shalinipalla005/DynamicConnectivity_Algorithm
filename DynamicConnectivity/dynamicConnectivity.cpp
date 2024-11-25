#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include "Graph1.cpp" // Assuming you have a header file for the Graph class

using namespace std;
using namespace chrono;

int main()
{
    // Redirecting input and output
    freopen("Input.txt", "r", stdin);
    freopen("Output111.txt", "w", stdout);

    // Variables to measure time
    auto prep_start = high_resolution_clock::now();
    auto prep_end = high_resolution_clock::now();
    auto updation_start = high_resolution_clock::now();
    auto updation_end = high_resolution_clock::now();
    auto query_start = high_resolution_clock::now();
    auto query_end = high_resolution_clock::now();
    auto io_start = high_resolution_clock::now();
    auto io_end = high_resolution_clock::now();

    // Reading input size
    int n, m;
    io_start = high_resolution_clock::now();
    cin >> n >> m;
    io_end = high_resolution_clock::now();

    // Graph preparation
    prep_start = high_resolution_clock::now();
    Graph g(n);
    prep_end = high_resolution_clock::now();

    // Processing queries
    for (int i = 0; i < m; i++)
    {
        string s;
        int a, b;

        io_start = high_resolution_clock::now();
        cin >> s >> a >> b;
        io_end = high_resolution_clock::now();

        a--;
        b--;

        if (s == "add")
        {
            // Adding an edge
            updation_start = high_resolution_clock::now();
            g.edge_insertion(a, b);
            updation_end = high_resolution_clock::now();
        }
        else if (s == "rem")
        {
            // Removing an edge
            updation_start = high_resolution_clock::now();
            g.edge_removal(a, b);
            updation_end = high_resolution_clock::now();
        }
        else
        {
            // Querying connectivity
            query_start = high_resolution_clock::now();
            bool ans = g.isConnected(a, b);
            query_end = high_resolution_clock::now();

            // Outputting the result
            io_start = high_resolution_clock::now();
            cout << (ans ? "YES" : "NO") << endl;
            cout <<"---------------------------------------------------" << endl;
            io_end = high_resolution_clock::now();
        }
    }

    // Recording timings
    ofstream updateFile, queryFile;
    // updateFile.open("dynamic_update.txt", ios::app);
    // queryFile.open("dynamic_query.txt", ios::app);

    auto prep_duration = duration_cast<microseconds>(prep_end - prep_start);
    auto updation_duration = duration_cast<microseconds>(updation_end - updation_start);
    auto query_duration = duration_cast<microseconds>(query_end - query_start);
    auto io_duration = duration_cast<microseconds>(io_end - io_start);

    // updateFile << updation_duration.count() << endl;
    // queryFile << query_duration.count() << endl;

    return 0;
}
