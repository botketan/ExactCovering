// To Access pretty print matrix function using header
#include "../Exact-Covering/inputGeneration.h"

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

int main()
{
    return 0;
}