## Week 1 (April 12 - April 16)
This week's goal was to finish file I/O and set up the classes that we need for our project. Specifically, we wanted to create:
 - Forest Class : Parent function for Node class where all the algorithms will run in.
 - Node Class : Has the information of all the nodes including it's copurchase index, path to linked node, etc.
 
Before the actual coding started, the team met up for a quick task distribution and Tyler guided us on the Git workflow that we will be using. We also splitted ourselves into two 2-man teams to work on different chunks of the project to maximize efficiency. To process our data into our C++ classes, we first had to read through every single line of the dataset and change it into the way we would like to process. </b>
Because our data consists of two tab seperated numbers, we decided to parse our data into a unordered_map, first element being the current point and second element being the second point.
In order to do that we implemented I/O function readFromFile() that reads the dataset and set up the objects in a way we want them to be in.

## Week 2 (April 19 - April 23)

This week's goal was to finish implementing the code to determine how influential each product is. The "influentiality" of a product is determined by how many connected purchases it triggers (the higher the number of connected purchases, the more "influential" it is). In our code, we call this the copurchasing index (COP index) of a product, and we determine each product's COP index by performing IDDFS.</b>.
Because we already had the set limit, we had to implement the Depth Limited Search part of IDDFS.</b>
After determining the COP indexes for every product, our project's objective is to then choose the top-N items of highest COP index (we define these topN products as most valuable). To have this 'choosing' process, we implemented another function filter(), which basically implements sorting.</b>
For example, if we want the top-10 products with largest COP index, we would set filter(10).</b>
After finishing the algorithms (IDDFS and filter), we created our own MakeFile and test cases for compilation and testing. After the mini tests work out, we succesfully ran our code with our actual Amazon dataset.</b> Soon Ha also implemented I/O code to output the filtered top-N products as well as its cop index to a separate txt file in main.cpp for better visualizing.</b>

## Week 3 (April 26 - May 2)

We implemented Tarjan's algorithm. This algorithm can be used on the top products and find strongly connected components on each top prodcut. We also added unit tests on multiple graphs to test the robustness of the algorithm. Next week's goal is to implement BFS and then tie everything together to draw insighful conclusions from the data sets. We'll also begin writing the final report once we have completed everything.

## Week 4 (May 2 - May 9)

Since we are done with our two algorithms, Shu Xian finished implementing the traversal (Breadth First Search) on our graph. The implementation itself is relatively straightforward as it shares a similar logic to IDDFS algorithm. Our BFS will return the total number of nodes within our graph that has been processed. By the end of this week, we are planning to polish up all the codes that we have, finish the documentation work needed for final submission and if all goes well, also complete our presentation recording. If all of these can be done, then next week will just be about making sure nothing goes wrong.



