# General Description 
The final deliverables of our project is all written into result_midpoint.txt file in Forest->Results Directory.

If both IDDFS and Tarjan's algorithms and BFS are executed, the output file will have three main parts, which correspond to the algorithms and traversals respectively. We also included one extra line at the very end that shows user input for convenience purposes.

1. The first part will consist of N lines (depending on the input for ranking N). Each of these N lines represent the items with highest copurchasing index (sorted with non-increasing order). 

2. The second part will have some j lines where j is not known beforehand. Each of the j lines represent one strongly connected component that is strictly greater than size 1.

3. The third part will only have one line, showing the total number of items being filtered from the raw dataset.

# Discoveries
1. From our raw dataset, our output suggests that most of the items with high copurchasing index lie in the latter half of our dataset (Most itemIDs are at least 10e4 and above).

2. In general, customers potential of copurchasing on Amazon website is quite high. Changing from IDDFS limit 2 to 3, we can see the copurchasing index for the top N products rising from ~100 to ~600.

3. From our Tarjan's algorithm, we observe that there aren't a lot of strongly connected components within our top N products. This suggests that the top N products are quite diverse and are likely of different categories. This indirectly shows that Amazon is a quite sustainable online selling platform (it will not easily crumble if one particular category becomes unpopular).

4. From the counting of items in BFS, we observe that with a limit of 3, and a ranking of top 100 products, we ended up having ~7% total number of items out of our raw dataset. This again implies Amazon's sales for that dataset is quite well. Note: raw dataset has 403394 items. (Consider selecting top-100 from 403394 is only 0.02%, and we ended up having ~7% is quite amazing).

# Correctness
The proof of the correctness of algorithm is being tested with the test cases we created.