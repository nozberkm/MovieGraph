# MovieGraph
This project contains the source code for the program that models actors and the movies they played in as a graph and connects actors that acted in the same movie. The model can then be used to find shortest paths between actors through movies using Dijkstra's algorithm. Using the adjacency matrix and squaring it gives us a representation of common neighbors for each actor and allows us to make predictions of new collaborations between actors. Through the use of a K-degenerate graph we can also build sub-graphs of k-cores that help us visualize strong connections within subcommunities in the graph.
