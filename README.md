# CS 225 Final Project - TEAM MIK

## <a href=https://drive.google.com/file/d/1SoMRuLDRyCz9MPvzV8PpQVfQ6b0XixZN/view> Video Presentation </a>

### Team Members
- Soonha Hwang (soonhah2)
- Shu Xian Lai (sxlai2)
- Tyler Kim (tkim139)
- Akshay Sivaraman (abs7)

## Table of Contents</br>
<ol>
  <li>
    <a href=#project-goal>Project Goal</a>
  </li>
  <li>
    <a href=#getting-started>Getting Started</a>
    <ul>
      <li>
        <a href=#prerequisites>Prerequisites</a>
      </li>
      <li>
        <a href=#installation>Installation</a>
      </li>
      <li>
        <a href=#execution>Execution</a>
      </li>
      <ul>
        <li>  
          <a href=#executing-testcases>Executing Testcases</a>
        </li>
      </ul>
    </ul>
      
  </li>
  <li>
    <a href=#location-of-code-data-and-results> Location of Code, Data, and Results</a>
  </li>
  <li>
    <a href=#extra-documents> Extra Documents</a>
  </li>
</ol>
  
## Project Goal
Whenever we surf in Amazon, Amazon always tempts us to purchase related products. For example, when I try to buy a shampoo, Amazon would show soaps and shower towels. When I try to buy a calculator, Amazon would suggest pens and pencils. The following image demonstrates Amazon's suggestions system when I searched for a monitor.

<p align="center">
  <a href="../master/assets/am_example.PNG">
    <img src="../master/assets/am_example.PNG" alt="amazon" width= 60%, height = 50%>
  </a>
</p>
We were curious about three things, which we tried to find out by project:
<ol>
  <li> What are the top-N items that render the most number of related purchases (IDDFS or Depth Limited Search)? </li>
  <li> Among the top-N products from step 1, what are the products that would be most profitable to promote on (Tarjan's Algorithm)? </li>
  <li> After filtering top-N products from the raw dataset, what are the total number of products we are left with? (Breadth First Search) </li>
</ol>


## Getting Started
You can follow few easy steps to execute our project.

### Prerequisites
To begin with, you will have to load llvm on EWS environment with `module load llvm`

### Installation
1. Clone this repository
   ```sh
   git clone https://github.com/soonhahwang/Finding-Related-Purchases-in-Amazon.git
   ```
2. Locate in correct directory. For more information on our directory structure, please refer to <a href=#location-of-code-data-and-results>Location of Code, Data, and Results</a>
   ```sh
   cd soonhah2-sxlai2-tkim139-abs7/Forest
   ```
### Execution
Inside the Forest directory, run make to compile the project. Execute `main` to run the project. 
```sh
make
./main
```
Following output will show on terminal. Input your own variables and see different results according to the different inputs!</br>
Note that all output is stored into a txt file in the results directory and our code assumes all user inputs are strictly legal according to this README and the prompts.
For example,
```
Enter limit for IDDFS (less than or equal to 3): 2
From the following input files
----------------------
1- SNAP Amazon Dataset 
2- sample testfile 1 
3- sample testfile 2 
4- sample testfile 3 
5- sample testfile 4
----------------------
Choose input file: 1
Enter ranking N: 100
Do you want to execute Tarjan's algorithm? (yes or no): yes
Do you want to execute BFS? (yes or no): no
```
Doing so will output results for IDDFS and Tarjan's Algorithm but not BFS. Also, in the example, we have selected `../Amazon6061.txt` for our input, but you can input any input data just by simply typing in the file path after `Enter input file: ` command.

#### Executing testcases
you can also run testcases with the following steps:
1. run <a href=../master/Forest/tests/test.cpp>test.cpp</a>
   ```
   make test
   ./test
   ```
2. Test can be run by `./test`, or can be run with `./test "test names"`. <a href=../master/Forest/tests/test.cpp>test.cpp</a> is located in `Forest/tests/`
   ```
   ./test "Checking IDDFS testcase 3"
   ```
3. Note for test suite: In our test suite, we created specific test cases for: Constructor (both Node and Forest class), File I/O, IDDFS, Tarjan's Algorithm (we call them SCC in our test cases description), BFS, and also some miscellaneous test cases that test some of the nested helper functions inside our main algorithms. For each algorithm & traversal, we created at least two different test cases to account for graphs of different nature. What each test case does should be fairly straightforward from the title of our test cases.

## Location of Code, Data, and Results
All our code, test suite and results are in the Forest directory. Our code is in the files "Forest.h", "Forest.cpp" and "main.cpp". Our test suite is in the Tests directory. Our results will be outputted into the "result_midpoint.txt" file (in the results directory). Our dataset is in the general directory - "Amazon0601.txt", while we have self made test cases from sample_testcase1.txt to sample_testcase4.txt in directory called /tests. In the /tests directory, you can also see the visualization of the sample input.
```
├── Forest
│   ├── Forest
│   ├── Forest.cpp
│   ├── Forest.h
│   ├── main.cpp
│   ├── results
│   │   └── result_midpoint.txt (stores result)
│   └── tests
│       ├── testcases.txt (4 self created test cases)
│       └── test.cpp
├── Amazon0601.txt (Main testcase)
├── README.md
├── Final Project Proposal.md
└── Team_Contract.md
```

## Extra Documents
Click to see our extra documents:
<ul>
  <li>
    <a href="/Team_Contract.md">Team Contract</a>
  </li>
  <li>
    <a href="/Final%20Project%20Proposal.md">Project Proposal</a>
  </li>
  <li>
    <a href="/Amazon0601.txt">Dataset Used</a>
  </li>
  <li>
    <a href="/Results.md">Results</a>
  </li>
</ul>

## Acknowledgement
Special thanks to Rishabh for being our good TA!
