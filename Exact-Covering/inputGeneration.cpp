#include "inputGeneration.h"

// Function to print the matrix in a raw binary format
// 'matrix' is a vector of sets where each set represents the items in a row
// 'k' is the number of distinct items (columns) in the matrix
void printMatrix(vector<set<int>> &matrix, int k) {
    // Redirect standard output to the file "input_raw.txt"
    freopen("input_raw.txt", "w", stdout);

    // Initialize a 2D vector 'raw' of size matrix.size() x k with all values set to 0
    // This will store the binary representation of the matrix
    vector<vector<int>> raw(matrix.size(), vector<int>(k, 0));

    cout<<matrix.size()<<" "<<k<<endl;

    // Loop through each row of the matrix
    for (int i = 0; i < matrix.size(); i++) {
        auto row = matrix[i]; // Extract the current row as a set of items

        // Loop through each item in the set and mark it as present in the binary matrix
        for (auto item : row) {
            raw[i][item] = 1; // Set corresponding column (item) to 1
        }
    }

    // Loop through each row of the binary matrix 'raw'
    for (int i = 0; i < matrix.size(); i++) {
        // Print the binary representation of the current row, separated by spaces
        for (int j = 0; j < k - 1; j++) {
            cout << raw[i][j] << " "; // Print all items except the last one with space
        }
        cout << raw[i][k - 1] << endl; // Print the last item without a trailing space
    }
}



// Function to print the matrix in a human-readable format
// 'matrix' is a vector of sets of integers representing the matrix
// 'k' is the number of distinct items allowed in each row
void prettyPrintMatrix(vector<set<int>> &matrix, int k) {
    // Redirect standard output to the file "input_matrix.txt"
    freopen("input_encoded.txt", "w", stdout);

    cout<<matrix.size()<<" "<<k<<endl;

    // Loop through each row of the matrix
    for (auto row : matrix) {
        string temp;
        // For each item in the row, append it to a string
        for (auto item : row) {
            temp += to_string(item) + " "; // Add item to string with a space
        }
        temp.pop_back(); // Remove the trailing space from the string
        cout << temp << endl; // Print the row
    }
}

// Function to generate a random matrix with 'n' rows and items up to 'k'
// Each row contains a random number of distinct items
vector<set<int>> generateMatrix(int n, int k) {
    vector<set<int>> nrows(n); // Vector of sets to store matrix rows

    // Loop through each row
    for (int i = 0; i < n; i++) {
        int numOfItems = rand() % k + 1; // Random number of items in the row

        // Add random distinct items to the row
        while (numOfItems--) {
            int randomItem = rand() % k + 1; // Generate random item between 1 and k
            nrows[i].insert(randomItem); // Insert item into the set (row)
        }
    }
    return nrows; // Return the generated matrix
}

// Function to generate CNF clauses based on the matrix
// Each clause ensures that specific pairs of items do not appear together
vector<vector<int>> genClauses(vector<set<int>>& matrix, int k) {
    vector<vector<int>> ItemsMapping(k + 1); // Map of items to their row indices
    int n = matrix.size(); // Number of rows

    // Loop through each row and map the items to their respective rows
    for (int i = 0; i < n; i++) {
        for (auto item : matrix[i]) {
            ItemsMapping[item].push_back(i + 1); // Store row index for each item
        }
    }

    vector<vector<int>> Clauses; // Vector to store generated clauses

    // Generate the clauses
    for (int i = 1; i <= k; i++) {
        vector<int> mainClause;

        // Generate a clause that includes all rows containing the current item
        for (auto x : ItemsMapping[i]) {
            mainClause.push_back(x); // Add row index to the clause
        }
        mainClause.push_back(0); // Clause terminator (0)
        Clauses.push_back(mainClause); // Add the clause to the list

        // Generate pairwise negative clauses to avoid item pairs in the same row
        for (int j = 0; j < ItemsMapping[i].size(); j++) {
            for (int k = j + 1; k < ItemsMapping[i].size(); k++) {
                Clauses.push_back({ -ItemsMapping[i][j], -ItemsMapping[i][k], 0 });
            }
        }
    }
    return Clauses; // Return the generated clauses
}

// Function to print the clauses in a DIMACS CNF format
// 'clauses' is a vector of CNF clauses
// 'n' is the number of variables
void prettyPrintClauses(vector<vector<int>>& clauses, int n) {
    // Redirect standard output to the file "pairwise_encoding.txt"
    freopen("pairwise_encoding.txt", "w", stdout);

    // Print the problem line in CNF format
    cout << "p cnf " << n << " " << clauses.size() << endl;

    // Loop through each clause and print it
    for (auto clause : clauses) {
        for (int i = 0; i < clause.size() - 1; i++) {
            cout << clause[i] << " "; // Print the clause literals
        }
        cout << clause[clause.size() - 1] << endl; // End of clause
    }
}

// Main function
int main() {
    srand(time(0)); // Seed the random number generator
    cout << "Input n and k :"; // Prompt for user input
    int n, k;
    cin >> n >> k; // Read 'n' (number of rows) and 'k' (number of items)

    // Generate the matrix and store it in 'matrix'
    auto matrix = generateMatrix(n, k);

    // Print the matrix to the file
    prettyPrintMatrix(matrix, k);

    //Print raw Matrix to the file
    printMatrix(matrix,k);

    // Generate the CNF clauses based on the matrix
    auto clauses = genClauses(matrix, k);

    // Print the clauses to the file in DIMACS format
    prettyPrintClauses(clauses, n);
}
