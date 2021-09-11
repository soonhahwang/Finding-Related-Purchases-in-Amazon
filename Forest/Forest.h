#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <stack>
#include <list>
using namespace std;

class Forest {
    public:
        struct Node {
            // Product ID (First column of txt file)
            long _itemId;
            // The co-purchasing index of the product
            long _copIndex;
            // Vector of connected nodes
            vector<Node*> _connected; 

            /**
             * Constructor to initialize a Node with itemId
             */
            Node(long itemId);

            // Default constructor
            Node();

        };

        // Default constructor of Forest class
        Forest();

        /**
         * Constructor to initialize an empty Forest with copLimit
         */
        Forest(int copLimit); 

        /**
         * Function to read from a text file and generate all the nodes and edges of the graph
         * @param file A string storing the file path to the txt file
         */        
        void readFromFile(string file);

        /**
         * Function to filter the Top-N products, based on the co-paurchasing index of each product, 
         * and store them in the vector _topProduct
         * @param size The number of top products to be stored. 
                       e.g. size = 30, we get top 30 products of highest copIndex
         */
        void filter(size_t size);

        /**
         * Function to perform Depth-Limited Search on a node to calculate it's co-purchasing index
         * @param start Pointer to the Node on which we perform Depth-Limited Search
         * @param limit The maximum depth to which we perform the IDDFS
         * @return the co-purchasing index of the Node, which is the number of distinct nodes visited
         */
        int IDDFS(Node* start, int limit);

        /**
         * Recursive helper method for IDDFS
         * @param start Pointer to starting Node on which we perform Depth-Limited Search
         * @param cur Pointer to the Node on which we are currently iterating
         * @param limit The maximum depth to which we perform Depth-Limited Search from cur
         * @param visited A map to keep track of which nodes are visited, to prevent crash
         * @return the co-purchasing index of the Node cur, excluding visited nodes
         */        
        int IDDFS_helper(Node* start, Node* cur, int limit, unordered_map<Node*, bool>& visited);
        
        // Getter method for _copLimit
        int get_copLimit();

        // Helps create _itemsMap
        void set_itemsMap(long idx, Node* node);

        // Getter method for _itemsMap
        unordered_map<long, Node*> get_itemsMap();

        // Getter method for _topProduct
        vector<long> get_topProduct();

        //Tarjan's Algorithm
        /**
         * Function which returns all adjacent vertices of a Node within _topProduct
         * @param idx The index of the product in _topProduct
         * @return a vector of pointers to Nodes which are in _topProduct and adjacent to the Node at idx
         */
        vector<Node*> adjVertices(int idx);

        /**
         * Function to find all the Strongly Connected Cmponents(SCCs) among the top products using Tarjan's Algorithm
         * @return A vector of strongly connected components, where each strongly connected component is represented
                   as an vector of Item IDs
         */
        vector<vector<long>> SCC();

        /**
         * Recursive helper method for SCC
         * @param u The index of the node in _topProduct that we are currently performing Tarjan's algorithm on
         * @param disc Stores discovery times of visited vertices
         * @param low Stores earliest visited vertex (the vertex with minimum discovery time) 
                      that can be reached from subtree rooted with current vertex
         * @param stackMember bool array to check if a node is within the stack or not
         * @param st pointer to a stack to store all the connected ancestors
         */
        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[], vector<vector<long>>& connectedComps);

        /**
         * Function to get the index of a node in _topProduct
         * @param v Pointer to the node we are searching
         * @return index of v in _topProduct 
         */
        int getIndex(Node* v); // Gets the index of v in _topProduct

        /**
         * Function to perform Breadth First Search.
         * This functions performs BFS only on the subgraph containing the top products 
         * and all nodes within a depth of _copLimit from their nearest top product. 
         * It does not perform BFS on the entire graph
         * @return the total number of Nodes traversed
         */
        unsigned long BFS();

        /**
         * Recursive helper function for BFS
         * @param node Current node on which we are traversing
         * @param memo map to keep track of visited nodes
         * @param limit Limit to keep track of max depth to which we perform BFS 
                        (So that we traverse only withing our desired subgraph)
         */
        unsigned long BFShelper(Node* node, std::unordered_map<Node*, bool>& memo, int limit);

    private:
        // A mapping from item ID to a pointer of the Node
        unordered_map<long, Node*> _itemsMap;
        // The most optimum products, as calculated by filter(). Stored as a vector of item IDs
        vector<long> _topProduct;

        // This is the co-purchasing limit. This should by default be 0, and is the limit we set for IDDFS. 
        int _copLimit;          
};