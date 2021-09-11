#include "Forest.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>

unsigned long Forest::BFS(){
    std::queue<Node*> bfsqueue;
    std::unordered_map<Node*, bool> visited;
    unsigned long count = 0;

    for(unsigned int m = 0; m<_topProduct.size();m++){
        count = count + BFShelper(_itemsMap[_topProduct[m]], visited, _copLimit);
    }
    return count;
}

unsigned long Forest::BFShelper(Node* node, std::unordered_map<Node*, bool>& memo, int limit){
    if(limit < 0){
        return 0;
    }
    unsigned long count;
    if(memo[node]){
        count = 0;
    }else{
        count = 1;
    }
    if(limit == 0){
        return count;
    }
    memo[node] = true;
    if(limit == 1){
        for(unsigned int i=0; i<node->_connected.size(); i++){
            if(!(memo[node->_connected[i]])){
                count++;
            }
            memo[node->_connected[i]] = true;
        }
        return count;   
    }
    for(unsigned int i=0; i<node->_connected.size(); i++){
        count = count + BFShelper(node->_connected[i], memo, limit-1);
    }
    return count;
}


Forest::Forest(){
    _copLimit = 0;
}

Forest::Forest(int copLimit){
    _copLimit = copLimit;
}

Forest::Node::Node(){
    Node::_itemId = -1; //set _itemID as default
    Node::_copIndex = -1; //set _copIndex to be -1 as default
}

Forest::Node::Node(long itemId){
    Node::_itemId = itemId;
    Node::_copIndex = 0;
}

void Forest::readFromFile(string file){
    std::ifstream myfile(file); //read from file to myfile
    int a, b;
    while(myfile >> a >> b){ //store first column to a, second to b with tab separated
        if(_itemsMap.find(a) == _itemsMap.end()){ //if we have not created a node yet
            Node* createNode = new Forest::Node(a); //create node
            _itemsMap[a] = createNode;  //allocate the address of node to the _itemsMap
        }
        if(_itemsMap.find(b) == _itemsMap.end()){ //if we have not created b node yet
            Node* createNode = new Forest::Node(b); //create node
            _itemsMap[b] = createNode; //allocate the address of b node to the _itemsMap
        }
        _itemsMap[a]->_connected.push_back(_itemsMap[b]); //push the address of b to _connected vector of _itemsmap[a]
    } 
}

void Forest::filter(size_t size){ //size is the number of rankings we want.
    for(auto &iter : _itemsMap){ //iterate through _itemsMap
        long index = iter.first; //we know first element of itemsmap is the index(itemID)
        Node* node = iter.second;//second is the address of that index
        node->_copIndex = IDDFS(node, _copLimit); //set copIndex of the node by running Depth Limited Search
    }

    std::vector<std::pair<long, long>> rank; //make a map of rank to help us rank the products according to copIndex

    for(auto &iter : _itemsMap){ //Iterate through _itemsMap

        long index = iter.first;                        //save the itemID in index
        long copIndex = iter.second->_copIndex;         //save copIndex here
        if(rank.size()<size) {
            rank.push_back(std::make_pair(copIndex, index)); //if vector is less than desired size, just push back
        }
        else{
            sort(rank.rbegin(), rank.rend()); //sort to check if the node we are pushing is greater than min.
            
            if(copIndex > rank[size-1].first){   //if so, pop back and replace
                rank.pop_back();
                rank.push_back(std::make_pair(copIndex, index));
            }
        }
    }
    sort(rank.rbegin(), rank.rend()); //sort from largest to smallest in rank

    for(auto &iter : rank){
        _topProduct.push_back(iter.second); //push in the rank of the index.
    }
}

/*
Perform IDDFS starting from the <start> node with the given <limit> 
and count the number of distinct nodes that are linked to <start>
Set the count of distinct linked nodes within the Node class's <_copIndex>
*/
int Forest::IDDFS(Node* start, int limit){
    unordered_map<Forest::Node*, bool> visited; //created map of visited to perfrom the recursive iteration
    return IDDFS_helper(start, start, limit, visited);
}

int Forest::IDDFS_helper(Node* start, Node* cur, int limit, unordered_map<Node*, bool>& bookkeep){
    
    int count = 0; //count is number of nodes it is connected to.

    if(limit == 1) { //base case
        bookkeep[cur] = 1; 
        count = cur->_connected.size(); //set count to be the number of connected nodes
        for(unsigned long i = 0; i<cur->_connected.size(); i++) { //delete all the duplicating nodes
            if(bookkeep[cur->_connected[i]]) count--;
            bookkeep[cur->_connected[i]] = 1;
        }
        return count;
    }
    
    if(limit == 0) return 0; //if limit = 0 simply return 0

    bookkeep[cur] = 1; //set the node as visited
    count += cur->_connected.size();          //for every node we visit, we need to add its branching factor
    for(unsigned long i = 0; i<cur->_connected.size(); i++){
        if(bookkeep[cur->_connected[i]]) count--; //if we have visited the node, we decrement the count 

        //perform IDDFS on each immediately neighboring node
        count = count + IDDFS_helper(start, cur->_connected[i], limit-1, bookkeep);
    }
    return count;
}


int Forest::get_copLimit(){
    return _copLimit;
};

void Forest::set_itemsMap(long idx, Forest::Node* node){
    _itemsMap[idx] = node;
}

unordered_map<long, Forest::Node*> Forest::get_itemsMap(){
    return _itemsMap;
}

std::vector<long> Forest::get_topProduct(){
    return _topProduct;
}

vector<Forest::Node*> Forest::adjVertices(int idx) {
    if (unsigned(idx) >= _topProduct.size()) {
        return vector<Forest::Node*>();
    }
    vector<Node*> adjVertices;
    long productId = _topProduct[idx];
    Node* product = _itemsMap[productId];
    
    for (Node* adj : product->_connected) {
        if (std::find(_topProduct.begin(), _topProduct.end(), adj->_itemId) != _topProduct.end()) {
            adjVertices.push_back(adj);
        }
    }
    return adjVertices;
}

void Forest::SCCUtil(int u, int disc[], int low[], stack<int> *st,
                    bool stackMember[], vector<vector<long>>& connectedComps)
{
    static int time = 0;
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
  
    // Go through all vertices adjacent to this
    vector<Node*>::iterator i;

    vector<Node*> edges = adjVertices(u);

    for (i = edges.begin(); i != edges.end(); ++i)
    {
        int v = getIndex(*i);  // v is current adjacent of 'u'
        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember, connectedComps);
  
            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            // Case 1 (per above discussion on Disc and Low value)
            low[u]  = min(low[u], low[v]);
        }
  
        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        // Case 2 (per above discussion on Disc and Low value)
        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }
  
    // head node found, pop the stack and print an SCC
    int w = 0;  // To store stack extracted vertices
    if (low[u] == disc[u])
    {
        vector<long> temp;
        while (st->top() != u)
        {
            w = (int) st->top();
            temp.push_back(_topProduct[w]);
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        temp.push_back(_topProduct[w]);
        connectedComps.push_back(temp);
        stackMember[w] = false;
        st->pop();
    }
}
  
// The function to do DFS traversal. It uses SCCUtil()
vector<vector<long>> Forest::SCC()
{
    vector<vector<long>> connectedComps;

    int *disc = new int[_topProduct.size()];
    int *low = new int[_topProduct.size()];
    bool *stackMember = new bool[_topProduct.size()];
    stack<int> *st = new stack<int>();
  
    // Initialize disc and low, and stackMember arrays
    for (int i = 0; unsigned(i) < _topProduct.size(); i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }
  
    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (int i = 0; unsigned(i) < _topProduct.size(); i++)
        if (disc[i] == -1)
            SCCUtil(i, disc, low, st, stackMember, connectedComps);

    delete[] disc;
    delete[] low;
    delete[] stackMember;
    delete st;

    return connectedComps;
}

int Forest::getIndex(Node* v) {
    for (int i = 0; unsigned(i) < _topProduct.size(); i++) {
        if (v->_itemId == _topProduct[i]) {
            return i;
        }
    }
    return -1;
}