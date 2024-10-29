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

// Generates Seinz encoding for atmost k out of n elements (1,..n)
void generateAtmostK(vector<vector<int>>&clauses, int n, int k, bool negate) {
    // for partial sums
    auto s = [n, k, negate](int i, int j) {
        if(!negate){
            return n + (i - 1) * k + j;
        }
        else {
            return n*(n-k) + n + (i-1)*k + j;
        }
    };

    // If xi is true then s(i,1) should be true
    for(int i=1; i<n; i++){
        clauses.push_back({(negate ? i : -i) , s(i,1)});
    }

    // For first clause s(1,j) shouldnt be true
    for(int j=2; j<=k; j++){
        clauses.push_back({-s(1,j)});
    }

    // Partial sum constraint (prefix sum)
    for(int i=2; i<n; i++)
    {
        for(int j=1; j<=k; j++){
            clauses.push_back({-s(i-1,j),s(i,j)});
            if(j>=2){
                clauses.push_back({negate ? i : -i,-s(i-1,j-1),s(i,j)});
            }
        }
    }

    // If k is attained then dont make xi true
    for(int i=2; i<=n && k>0; i++)
    {
        clauses.push_back({-s(i-1,k),negate ? i : -i});
    }
}


void generateExactKOptimised(vector<vector<int>>&clauses, int n, int k)
{
    // Atmost k
    generateAtmostK(clauses,n,k,false);

    // Atleast k = Atmost n-k false
    generateAtmostK(clauses, n, n-k, true);
}

// To print the clauses in DIMACS Format
// n is the number of clauses
void prettyPrintClauses(vector<vector<int>>& clauses, int n, int k,string fileName) {
    // Redirect standard output to the file defined by fileName
    freopen(fileName.append(".txt").c_str(), "w", stdout);

    // Print the problem line in CNF format
    cout << "p cnf " << n + n*k + n*(n-k) << " " << clauses.size() << endl;

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
                    ans.push_back({-i,-j,-k});
                }
            }
        }
    }
}

int main()
{
    int n = 99;
    int k = 27;
    vector<vector<int>>ans;
    generateExactKOptimised(ans,n,k);
    // No 3 equally spaced ones constraints
    addNoThreeEquallySpacedConstraint(ans,n);
    
    prettyPrintClauses(ans,n,k,"problem_a1");
    return 0;
}