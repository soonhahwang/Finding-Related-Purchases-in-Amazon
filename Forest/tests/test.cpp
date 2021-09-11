#include "../cs225/catch/catch.hpp"

#include "../Forest.h"

#include <iostream>
// #include <vector>
#include <unordered_map>
// #include <fstream>
// #include <string>

TEST_CASE("Checking Initialization 1"){
    Forest forest = Forest();
    REQUIRE(0 == forest.get_copLimit());
}

TEST_CASE("Checking Initialization 2"){
    Forest forest1 = Forest(1);
    Forest forest2 = Forest(2);
    Forest forest3 = Forest(3);
    REQUIRE(1 == forest1.get_copLimit());
    REQUIRE(2 == forest2.get_copLimit());
    REQUIRE(3 == forest3.get_copLimit());
}

TEST_CASE("Checking Node Creation 1"){
    Forest forest = Forest();
    Forest::Node* createNode = new Forest::Node();
    forest.set_itemsMap(1, createNode);

    REQUIRE(createNode == forest.get_itemsMap()[1]);
}

TEST_CASE("Checking Node Creation 2"){
    Forest forest = Forest();
    vector<Forest::Node*> nodes;

    for(long i = 0; i<5; i++){
        Forest::Node* createNode = new Forest::Node(i);
        nodes.push_back(createNode);
        forest.set_itemsMap(i, createNode);
    }

    REQUIRE(nodes[0] == forest.get_itemsMap()[0]);
    REQUIRE(nodes[4] == forest.get_itemsMap()[4]);
    REQUIRE(nodes[1] == forest.get_itemsMap()[1]);
    REQUIRE(nodes[3] == forest.get_itemsMap()[3]);
    REQUIRE(nodes[2] == forest.get_itemsMap()[2]);

    REQUIRE(5 == forest.get_itemsMap().size());
}

TEST_CASE("Checking readFromFile 1"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase1.txt");
    REQUIRE(3 == forest.get_itemsMap()[1]->_connected.size());
    REQUIRE(3 == forest.get_itemsMap()[2]->_connected.size());
    REQUIRE(2 == forest.get_itemsMap()[3]->_connected.size());
    REQUIRE(8 == forest.get_itemsMap().size());
}

TEST_CASE("Checking IDDFS Limit 1"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase1.txt");

    REQUIRE(3 == forest.IDDFS(forest.get_itemsMap()[1], 1)); 
    REQUIRE(3 == forest.IDDFS(forest.get_itemsMap()[2], 1));
    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[3], 1));
}

TEST_CASE("Checking IDDFS Limit 2.1"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase1.txt");

    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[1], 2));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[3], 2));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[2], 2));
}

TEST_CASE("Checking IDDFS Limit 2.2"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase2.txt");

    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[1], 3));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[1], 2));
}

TEST_CASE("Checking IDDFS testcase 3 "){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase3.txt");

    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[1], 1));
    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[2], 1));
    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[3], 1));
    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[1], 2));
    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[1], 3));

    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[8], 1));
    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[9], 1));
    REQUIRE(4 == forest.IDDFS(forest.get_itemsMap()[10], 6));
    REQUIRE(4 == forest.IDDFS(forest.get_itemsMap()[11], 6));
    REQUIRE(4 == forest.IDDFS(forest.get_itemsMap()[12], 6));

}

TEST_CASE("Checking IDDFS Final"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase4.txt");
    
    //testing limit of 1
    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[1], 1));
    REQUIRE(4 == forest.IDDFS(forest.get_itemsMap()[6], 1));
    REQUIRE(1 == forest.IDDFS(forest.get_itemsMap()[16], 1));

    //testing limit of 2
    REQUIRE(4 == forest.IDDFS(forest.get_itemsMap()[1], 2));
    REQUIRE(7 == forest.IDDFS(forest.get_itemsMap()[13], 2));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[19], 2));
    
    //testing limit of 3
    REQUIRE(10 == forest.IDDFS(forest.get_itemsMap()[5], 3));
    REQUIRE(7 == forest.IDDFS(forest.get_itemsMap()[21], 3));
    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[19], 3));

    //testing limit of 4
    REQUIRE(9 == forest.IDDFS(forest.get_itemsMap()[1], 4));
    REQUIRE(11 == forest.IDDFS(forest.get_itemsMap()[3], 4));
    REQUIRE(14 == forest.IDDFS(forest.get_itemsMap()[6], 4));
    REQUIRE(7 == forest.IDDFS(forest.get_itemsMap()[11], 4));

    //testing limit of 5
    REQUIRE(14 == forest.IDDFS(forest.get_itemsMap()[3], 5));
    REQUIRE(10 == forest.IDDFS(forest.get_itemsMap()[11], 5));
    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[17], 5));

}

TEST_CASE("Checking filter 1"){
    Forest forest = Forest(1);
    forest.readFromFile("tests/sample_testcase1.txt");
    forest.filter(3);
    REQUIRE(1 == forest.get_topProduct()[1]);
    REQUIRE(2 == forest.get_topProduct()[0]);
    REQUIRE(3 == forest.get_topProduct()[2]);
}

TEST_CASE("Test Adjacent Vertices"){
    Forest forest = Forest(1);
    forest.readFromFile("tests/sample_testcase1.txt");
    forest.filter(3);
    // Top 3 products are 1, 2, 3
    
    vector<Forest::Node*> adj1 = forest.adjVertices(1);
    vector<Forest::Node*> adj2 = forest.adjVertices(0);
    vector<Forest::Node*> adj3 = forest.adjVertices(2);
    
    REQUIRE(2 == adj1[0]->_itemId);
    REQUIRE(3 == adj1[1]->_itemId);
    REQUIRE(1 == adj2[0]->_itemId);
    REQUIRE(3 == adj2[1]->_itemId);
    REQUIRE(2 == adj3[0]->_itemId);
}

TEST_CASE("SCC on graph with a single strongly connected component"){
    Forest forest = Forest(1);
    forest.readFromFile("tests/sample_testcase1.txt");
    forest.filter(3);
    // Top 3 products are 1, 2, 3
    vector<vector<long>> expected = {{3, 1, 2}};
    vector<vector<long>> actual = forest.SCC();

    REQUIRE(expected == actual);
}

TEST_CASE("SCC on graph with 2 strongly connected components"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase2.txt");
    forest.filter(10);

    vector<vector<long>> expected = {{10}, {5, 1, 3, 2, 4, 6, 7}};
    vector<vector<long>> actual = forest.SCC();

    REQUIRE(expected == actual);
}

TEST_CASE("SCC on disconnected graph"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase3.txt");
    forest.filter(12);

    vector<vector<long>> expected = {{8, 9, 10, 11, 12}, {7}, {6}, {5}, {4}, {3}, {2}, {1}};
    vector<vector<long>> actual = forest.SCC();

    REQUIRE(expected == actual);
}

TEST_CASE("BFS test with cop_limit 2") {
    Forest forest = Forest(2);
    forest.readFromFile("tests/sample_testcase1.txt");
    forest.filter(3);
    long BFS_count = forest.BFS();
    REQUIRE(BFS_count == 7);
    
}

TEST_CASE("BFS test with cop_limit 3") {
    Forest forest = Forest(3);
    forest.readFromFile("tests/sample_testcase2.txt");
    forest.filter(3);
    long BFS_count = forest.BFS();
    REQUIRE(BFS_count == 8);
}

TEST_CASE("BFS on a disconnected graph") {
    Forest forest = Forest(1);
    forest.readFromFile("tests/sample_testcase2.txt");
    forest.filter(4);
    long BFS_count = forest.BFS();
    REQUIRE(BFS_count == 7);
}