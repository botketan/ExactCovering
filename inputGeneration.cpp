#include<bits/stdc++.h>
#include <bitset>
using namespace std;

void prettyPrint(vector<set<int>> &matrix){
    freopen ("input_matrix.txt", "w", stdout);
    for(auto row :matrix){
        for(auto item : row){
            cout<<item<<" ";
        }
        cout<<endl;
    }
}

vector<set<int>> generateMatrix(int n,int k){
    vector<set<int>> nrows(n);
    for(int i =0;i<n;i++){
        int numOfItems = rand()%k +1;
        while(numOfItems--){
            int randomItem = rand()%k +1;
            nrows[i].insert(randomItem);
        }
    }
    return nrows;
}

int main(){
    srand(time(0));
    cout<<"Input n and k :";
    int n,k;
    cin>>n>>k;
    auto matrix = generateMatrix(n,k);
    prettyPrint(matrix);
}