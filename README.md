# ExactCovering


## InputGenerartion.cpp

### Usage
The program supports input generation and encoding as well as simply reading from `input_raw.txt` file and generating encoding.
The program generates 3 different types of encoding pairwise, bitwise and matrix encoding.
To take input from  `input_raw.txt` file. Comment out the following section from code at line 404
```
//genInputAndEncoding(true); // Comment out if using custom input
```


Example use Case. Here n represents no. of rows and k reperesents number of items. Do note that the first line in each input file denotes n and k. Then the next n rows of input_encoded contain items corresponding to row. Each item is represented by it's number. For example if number 2 is present in row 3 then row 3 has item 2. Refer to Dancing Links and input raw to better understand the input
```
g++ inputGeneration.cpp
.\a.exe
Input n and k :3 6
```

### Input Encoded
The file `input_encoded.txt` Contains a better encoded version of input matrix. The first two numbers denote n (Number of rows) and k (Number of columns). The next n lines contain the items that ith row holds. For example if row 1 hold items 3,4,6 then the 1st row will be 3 4 6.
Example file
```
3 8
3 4 6
1 2 3 4 5
1 5 7 8
```

### Encoding files
All the `*_encoding.txt` files contain a specific encoding as denoted by there name for the problem. All these files are input for sat solvers and follow this pattern.
```
p cnf V C
Followed by C lines
```

Here p denotes a propositional formula. cnf denotes cnf formula. C denotes the number of clauses and V denotes the number of variables in the formula.