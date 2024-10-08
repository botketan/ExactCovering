// To Access pretty print matrix function using header
#include "../Exact-Covering/inputGeneration.h"
#include <thread>
#include <mutex>

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
    vector<vector<int>>ans;
    vector<int>temp;
    generateExactK(ans,temp,20,6,0,true);
    //freopen("output.txt","w",stdout);
    for(auto x : ans)
    {
        for(auto y: x){
            cout<<y<<" ";
        }
        cout<<endl;
    }
    return 0;
}