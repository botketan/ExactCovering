#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include<bits/stdc++.h>
#include <bitset>
using namespace std;

void printMatrix(vector<set<int>> &matrix, int k);
void prettyPrintMatrix(vector<set<int>> &matrix, int k);
vector<set<int>> generateMatrix(int n, int k);
vector<vector<int>> genClauses(vector<set<int>>& matrix, int k);
void prettyPrintClauses(vector<vector<int>>& clauses, int n);

#endif
