# Social Network Analysis
A basic look into analysis of Social Networks (using C)

A simple representation of a social network through a graph, where each of the nodes represents a person inside the network:
  - If the person has many incoming edges (high indegree), he/she is followed by many people (or is popular)
  - If there are a large number of outgoing edges (high outdegree), he/she follows many other people in the network
  
How do we analyse this graph, this data?
The centrality measures tell us about the state of the network.
(Since the graph ADT used is a directed graph, the outdegree and indegree of a node of the network may vary)
1. Indegree centrality is simply the number of people that follow the person represented by the current node
2. Similarly, outdegree centrality is the number of people that the person follows.
3. Degree centrality represents the number of links to and from the current node.
4. Closeness Centrality = number of nodes connected to the current node/number of nodes in the graph. Thus it is a measure of the percentage of the nodes in the network the current node is connected to, directly or indirectly.
5. Betweenness Centrality = number of paths from node a to node b/number of paths from a to b through the current node. Gives a measure of how often will a shortest path between two nodes pass through the current node.

Furthermore the LanceWilliamsHAC.c file tries to apply the Lance Williams algorithm to create clusters out of the graph i.e. group the nodes close to each other, in a further attempt to understand the nature of the graph that represents a social network.

