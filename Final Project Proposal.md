# Final Project Proposal - TeamMIK

## Leading Question
Suppose we are the owners of Amazon, and we want to shrink the number of products that we are selling on the platform and we want to do so as optimally as possible. 
In other words, we want to find products that render the most number of other related purchases given the co-purchasing dataset.

To answer the leading question, we will:
1. Find top-N nodes with the most co-purchase index using IDDFS,
2. Decide which products to promote on by using Tarjan's Algorithm,
3. Find the products with high potential using Djisktra's Algorithm.

This will be described more in detail in section <strong>Graph Traversal</strong> and <strong>Graph Algorithm</strong>.

## Dataset Acquisition and Processing
We will be using "Amazon product co-purchasing network" from Stanford's Network Dataset (SNAP). The dataset is stored in a .txt file 
with each node representing an item and directed edges of node A to node B representing "customer bought item A, customer therefore also bought item B".

Data processing will involve collapsing multigraph into a simple graph, and performing Iterative Deepening Depth First Search (IDDFS) on each node to determine which 
item links to the most number of nodes given a certain depth.

Link to dataset can be found at [SNAP-Amazon Product co-purchasing Network](http://snap.stanford.edu/data/amazon0505.html)

## Graph Traversal
The graph traversal that we need to implement should be IDDFS because we take the assumption that customers have a limit of co-purchasing.
By using IDDFS, we can set the limit on how much co-purchasing can possibly happen, possibly generating various interesting outcomes based on the set limits.
Simply put, by using IDDFS we will calculate the number of unique nodes a certain node can traverse on. 
The number of nodes that can traverse on will be the co-purchase index of the product, which determines the extent of influence of the certain product.
We will hence rank the top_N nodes with the highest co-purchase index. These top-N nodes will be implied as "Most Influencial Product" listed in Amazon.

## Graph Algorithm

|Purpose          |Algorithm|Explaination|
|:---------------|---------|------------|
|Deciding　　　　 which products to promote on| Tarjan's Algorithm |If the products(nodes) are strongly connected, it will be beneficial for Amazon to promote such products rather than other individual nodes. That being said, we will use Tarjan's Algorithm to find all strongly connected components to determine which items should be offering promotions. Also, because the size of the strongly connected components can be very large, we will come up with a certain threshold that caps the maximum size of the conencted nodes|
|Finding Potentially Powerful Product| Dijsktra's Algorithm | We will use Dijsktra's Algorithm to find the shortest path between 2 nodes, the first node being one of the top-N hightest co-purchase indices we've determined using IDDFS (_A_), and the second node being one of the remaining nodes (_B_). Based on how short the path of node is from _A_ to _B_, we can determine which products have the most potential.|

## Timeline

| Time | Description |
|-----:| ----------- |
|April 09th|Finish Final Project Proposal and Teammate Contract|
|April 16th| First group meeting to set up goals and weekly targets.</br> **Target:** Finish implementing IDDFS |
|April 23rd| Second meeting. </br> **Tagret:** Finish implementing Tarjan's Algorithm|
|April 30th| Third meeting. </br> **Target:** Finish implementing Dijsktra's Algorithm|
|May 07th| Fourth meeting. </br> **Target:** Using the algorithms to answer topic question/debugging|
|May 08th ~ May 11th | Prepare for project deliverables|
|May 12th| Final Project Deliverables|
