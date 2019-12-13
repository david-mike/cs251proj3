# 

Brute Force Solution.
Brute force solution only considers sisuations of C=4, 5, 6.
It iterates through all the subsets, from 00000...00000 to 11111...11111.
The complexity is O(2^N).

Symbol Table Solution.
Symbol table solution deals with sisuations of C=4, 5, 6, 8, 10.
1. Write a function for operator -=.
2. Create a map in Symbol constructor. The map contains all the subsets of the last C/2*B items from table T. The key of the map is the subset_sum of one subset, and the value of the map is a key vector. The key vector will contains all the subsets which have the same subset_sum value.
3. In the decrypt function, it loops through the rest combinations of the first N - C/2*B items of table T. Each loop, we get a sum. The encrypted password subtracts the sum, and get a result. We look up the result in the map. If we find it in the map, it means we find the password. Password equals to value in the map + value in the respective loop.
© 2019 GitHub, Inc.
