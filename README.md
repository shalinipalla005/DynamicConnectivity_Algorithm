# Dynamic Connectivity Checker

This project provides an efficient implementation for handling dynamic connectivity queries in a graph. It supports operations to add and remove edges dynamically and check connectivity between vertices. 
The project leverages advanced data structures such as **Splay Trees** and **Spanning Forests** for optimal performance.

## Features

- Dynamically add and remove edges in a graph.
- Check connectivity between any two vertices.
- Efficiently manage connected components using a **Spanning Forest**.
- Outputs results to a file for better analysis and debugging.
- Provides timing metrics for various operations (preparation, updates, queries, I/O).

---

## Project Structure

1. **`dynamicConnectivity.cpp`**  
   - The main driver program for handling input, processing queries, and outputting results.  
   - Includes performance tracking for different stages (I/O, graph updates, queries).  
   - Redirects input from `Input.txt` and writes results to `Output111.txt` and also `Output.txt`.  

2. **`Graph1.cpp`**  
   - Implements the graph operations, such as edge insertion, removal, and connectivity checks.  
   - Relies on **Splay Forests** and **Spanning Forests** for dynamic graph updates.  

3. **`SplayForest1.cpp`**  
   - Provides the implementation of a **Splay Tree** to manage the internal representation of connected components efficiently.  
   - Includes tree operations like rotations, splits, merges, and in-order traversals.  

4. **`SpanningForest1.cpp`**  
   - Implements a **Spanning Forest** to track connected components of the graph.  
   - Allows efficient edge addition and removal.  
   - Maintains connectivity information for components and supports operations like making a node the root of its component.  

5. **`Input.txt`**  
   - Input file containing the list of queries to be processed.  
   - Format:
     ```
     V X
     add u v
     check u v
     rem u v
     ```
     - `V`: Number of vertices.
     - `X`: Number of queries.
     - `add u v`: Add an edge between vertices `u` and `v`.
     - `check u v`: Check if vertices `u` and `v` are connected.
     - `rem u v`: Remove the edge between vertices `u` and `v`.

6. **`Output111.txt`**  
   - Output file containing results of connectivity queries (`YES` or `NO`).  

---

## Compilation and Running

### 1. Compilation

Compile the necessary files into executables using `g++`:
```bash
g++ dynamicConnectivity.cpp -o dynamicConnectivity
```

### 2. Running the Program

Run the program with the following command:
```bash
./dynamicConnectivity
```

The program reads input from `Input.txt` and outputs the results in `Output111.txt`.

---

## Debugging and Metrics

- **Debugging Output**:  
   - Modify the `DEBUG` flag in `splayforest.cpp` to enable detailed tree structure outputs.  
   - When `DEBUG = 1`, the tree's edges and structure will be printed during execution.  

- **Timing Metrics**:  
   - The `dynamicConnectivity.cpp` file records and outputs the time taken for:
     - Graph preparation.
     - Edge updates (additions and removals).
     - Connectivity queries.
     - Input/Output operations.  
   - These metrics can be logged to files for further analysis.

---

## Example

### Input (`Input.txt`)
```
5 5
add 1 2
add 2 3
check 1 3
rem 2 3
check 1 3
```

### Output (`Output111.txt`)
```
YES
NO
```

### **`Output.txt`**

- **Purpose**:  
   - This file logs:
     - The state of the graph at various levels after operations (`T` and `NT` levels, edges in the spanning forest, and non-tree edges).
     - Results of `check` queries in the format `YES` or `NO`, along with descriptive messages for each query.

- **Contents**:  
  - **Tree and Non-Tree Edge Representation**:
    - `T` and `NT` denote "tree edges" and "non-tree edges" at different hierarchical levels (3T, 3NT, 2T, etc.).
    - The numbers before `T` or `NT` indicate the hierarchical level.
    - For example:
      ```
      3T (1, 2); (2, 3);
      3NT (1, 3);
      ```
      This means edges `(1, 2)` and `(2, 3)` are tree edges at level 3, while `(1, 3)` is a non-tree edge.
  - **Query Results**:
    - Connectivity checks are formatted like:
      ```
      (1, 10) is connected
      YES
      ---------------------------------------------------
      ```
    - Each result is followed by a separator for clarity.

- **Example**:
  - If a query checks the connection between vertices `1` and `10`, and they are connected, the output is:
    ```
    (1, 10) is connected
    YES
    ---------------------------------------------------
    ```

---

### How `Output.txt` Fits

1. **For Debugging**:  
   - The state of tree and non-tree edges is recorded after every operation, helping to trace the logic and verify correctness.
   - The hierarchical representation of edges provides insights into the forest's structure.

---

#### Output Files

1. **`Output.txt`**  
   - Logs the graph's state at different levels (tree and non-tree edges).  
   - Provides results for connectivity queries (`YES` or `NO`) in a structured format.

2. **Example Content of `Output.txt`**:
   ```
   3T (1, 2); (2, 3); (4, 5);
   3NT (1, 3);
   2T 
   2NT 
   ...
   (1, 10) is connected
   YES
   ---------------------------------------------------
   ```
---

## Dependencies

- **C++ Standard Library** (`<bits/stdc++.h>`)
- Files required for this program:
  - `dynamicConnectivity.cpp`
  - `Graph1.cpp`
  - `SplayForest1.cpp`
  - `SpanningForest1.cpp`

---

## Notes

- Ensure that all required files are in the same directory before compilation.
- Modify `Input.txt` to test different graph configurations and queries.
- Use the debugging and timing metrics to understand and improve performance.
The `Output.txt` file provides detailed feedback on the state of the graph after each operation,
along with results for connectivity queries. 
---
