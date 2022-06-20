# Project for the Algorithm Analysis and Synthesis

Given a certain data structure, further defined in "Project 1.pdf", the program should output information about sub-regions of the data.

Thus the tarjan algorithm was implemented in C++ to find strongly connected components.

## Complexity Analysis
A complexity analysis of the algorithm was also performed:
Initialization:
* Given V vertices, the graph is created in O(V)
* Then, the edges are added in O(E) since they are presented in an adjacency list.

Tarjan Algorithm:
* The visit function is called recursively, one time per edge, thus being O(V+E), since all the other computations are O(1), for comparisions and removals and O(2V) for the update of the SCC ids.

Result output:
* Given that the edge set is implemented with a binary tree, the insertion time is O(log(n)). In the worst case, where every edge belongs to the SCC the complexity is O((V+E) log(E))


## Experimental Evaluation

An experiment was also made, given 100 runs where the vertex quantity varied from 10k and 604k. The number of edges is always 3 times the number of edges and in each test, 1000 SCC were created.

![image](https://user-images.githubusercontent.com/16226383/174685944-3b68623c-8738-4e87-9dcc-31a1d4dd81e6.png)
