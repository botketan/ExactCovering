#include<bits/stdc++.h>
#include <bitset>
using namespace std;

void prettyPrintMatrix(vector<set<int>> &matrix){
    freopen ("input_matrix.txt", "w", stdout);
    for(auto row :matrix){
        string temp;
        for(auto item : row){
            temp+= to_string(item) +" ";
        }
        temp.pop_back();
        cout<<temp<<endl;
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

vector<vector<int>> genClauses(vector<set<int>>& matrix,int k){
    vector<vector<int>> ItemsMapping(k+1);
    int n = matrix.size();
    for(int i =0;i<n;i++){
        for(auto item:matrix[i]){
            ItemsMapping[item].push_back(i+1);
        }
    }
    vector<vector<int>> Clauses;
    for(int i =1;i<=k;i++){
        vector<int> mainClause;
        for(auto x:ItemsMapping[i]){
            mainClause.push_back(x);
        }
        mainClause.push_back(0);
        Clauses.push_back(mainClause);
        for(int j =0;j<ItemsMapping[i].size();j++){
            for(int k = j+1;k<ItemsMapping[i].size();k++){
                Clauses.push_back({-ItemsMapping[i][j],-ItemsMapping[i][k],0});
            }
        }
    }
    return Clauses;
}

void prettyPrintClauses(vector<vector<int>>&clauses,int n){
    freopen ("pairwise_encoding.txt", "w", stdout);
    cout<<"p cnf "<<n<<" "<<clauses.size()<<endl;
    for(auto clause : clauses){
        for(int i =0;i<clause.size()-1;i++){
            cout<<clause[i]<<" ";
        }
        cout<<clause[clause.size()-1]<<endl;
    }
}


int main(){
    srand(time(0));
    cout<<"Input n and k :";
    int n,k;
    cin>>n>>k;
    auto matrix = generateMatrix(n,k);
    prettyPrintMatrix(matrix);
    auto clauses = genClauses(matrix,k);
    prettyPrintClauses(clauses,n);
}