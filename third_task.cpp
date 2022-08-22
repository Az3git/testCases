#include<iostream>

using namespace std;
const int big = 100000000;
const int MAXN = 901;
const int MAXM = 901;
const int MAXP = 900001;

struct DLX
{
    // n rows, m columns, size nodes
    int n, m, size;
    // Parts of a two-dimensional doubly linked list
    int U[MAXP], D[MAXP], L[MAXP], R[MAXP], row[MAXP], col[MAXP];
    int H[MAXN], S[MAXM];
    // res writes the number of lines and ans writes the possible solution
    int res, ans[MAXN];

    void init(int x, int y)
    {
        n = x, m = y;
        // Creation of the first elements of the list. 
        // The null element is the head, and m are the head nodes of the columns.
        for (int i = 0; i <= m; ++i) {
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        memset(S, 0, sizeof(S));
        memset(H, -1, sizeof(H));
    }
    void push(int r, int c)
    {
        size++; row[size] = r; col[size] = c; S[c]++;
        // Insert node
        D[size] = D[c]; U[D[c]] = size;
        U[size] = c; D[c] = size;
        // If there are no elements in the string, H[r] marks the starting node of the string
        if (H[r] < 0) {
            H[r] = L[size] = R[size] = size;
        }
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void covering(int c)
    {   // Deleting a column ñ
        L[R[c]] = L[c]; R[L[c]] = R[c];
        // Deleting rows by column node c
        for (int i = D[c]; i!= c; i = D[i]) {
            for (int j = R[i]; j!= i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[col[j]];
            }
        }
    }
    void uncovering(int c)
    {
        // Restoring rows by column node c
        for (int i = U[c]; i!= c; i = U[i]) {
            for (int j = L[i]; j != i; j = L[j]) {
                U[D[j]] = j; D[U[j]] = j;
                ++S[col[j]];
            }
        }
        // Column recovery
        L[R[c]] = c; R[L[c]] = c;
    }
    bool dance(int deep)
    {
        if (res < deep) return false;
        // An empty matrix means that a solution has been found
        if (R[0] == 0) {
            res = min(res, deep);
            return true;
        }
        // Finding the column with the fewest nodes to remove
        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i]) {
            if (S[i] < S[c]) {
                c = i;
            }
        }
        covering(c);
        for (int i = D[c]; i != c; i = D[i]) {
            // current decision
            ans[deep] = row[i];
            
            for (int j = R[i]; j != i; j = R[j])
                covering(col[j]);
            // Moving to the next level
            dance(deep + 1);
            // Go back one level, restore columns
            for (int j = L[i]; j != i; j = L[j])
                uncovering(col[j]);
        }
        
        uncovering(c);
        return false;
    }
}dlx;
int n, m, p;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        
        cin >> n >> m >> p;
        // Initialize a table with size p-1 by n*m
        dlx.init(p - 1, n * m);
        for (int i = 0; i < p; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            for (int j = x1; j < x2; ++j) {
                for (int k = y1; k < y2; ++k) {
                    dlx.push(i, n * k + j + 1);
                }
            }
        }
        dlx.res = big;
        dlx.dance(0);
        if (dlx.res == big) {
            cout << "-1\n";
        
        }
        else {
            cout << dlx.res << "\n";
           
        }
    }
    return 0;
}
