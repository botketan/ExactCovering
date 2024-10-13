/**
 * Find a bitstring S = x1x2...xn such that there are exactly k ones and no three equally spaced ones
 */
#include<bits/stdc++.h>

using namespace std;

// Function to generate all K subet disjunctions of n
// If `negation` is true, it create clauses with negative values
void generateExactK(vector<vector<int>>&ans, vector<int>&temp, int n, int k, int prev, bool negation)
{
    if(k==0){
        ans.push_back(temp);
    }
    else{
        for(int i=prev+1; i<=n; i++)
        {
            temp.push_back(negation ? -i : i);
            generateExactK(ans,temp,n,k-1,i,negation);
            temp.pop_back();
        }
    }
}

// To print the clauses in DIMACS Format
// n is the number of clauses
void prettyPrintClauses(vector<vector<int>>& clauses, int n, string fileName) {
    // Redirect standard output to the file defined by fileName
    freopen(fileName.append(".txt").c_str(), "w", stdout);

    // Print the problem line in CNF format
    cout << "p cnf " << n << " " << clauses.size() << endl;

    // Loop through each clause and print it
    for (auto clause : clauses) {
        for (int i = 0; i < clause.size(); i++) {
            cout << clause[i] << " "; // Print the clause literals
        }
        cout << 0 << endl; // End of clause
    }
}

void addNoThreeEquallySpacedConstraint(vector<vector<int>>&ans, int n){
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            for(int k=j+1; k<=n; k++){
                if(j-i == k-j){
                    ans.push_back({-i,-j,-k, 0});
                }
            }
        }
    }
}

int main()
{
    int n = 20;
    int k = 6;
    vector<vector<int>>ans;
    vector<int>temp;
    // No more than k variables should be true
    generateExactK(ans,temp,n,k+1,0,true);
    temp.clear();
    // Atleast k variables should be true
    generateExactK(ans,temp,n,n-k+1,0,false);

    // No 3 equally spaced ones constraints
    addNoThreeEquallySpacedConstraint(ans,n);
    
    prettyPrintClauses(ans,n,"problem_a1");
    return 0;
}