#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int N = 10001000;
#define lnum long long

lnum a[N];
lnum pairSum[N];

//binary search for the nearest lower value to the value M
int search(int l, int r, lnum M)
{
    int mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (pairSum[mid] <= M) l = mid + 1;
        else  r = mid;
    }
    return l - 1;
}
int main2()
{
    int n, k, caseNum = 1;
    lnum el, m;

    while (true)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        k = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> el;
            if (el <= m) {
                
                a[k++] = el;
            }
        }
        a[k] = 0;
        int p = 0;

        // ñreating an array, with the pairwise sum of all elements of the original array
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
            {
                if (a[i] + a[j] <= m)
                    pairSum[p++] = a[i] + a[j];
            }
        sort(pairSum, pairSum + p);

        lnum ans = 0;
        for (int i = 0; i < p; i++)
        {
            lnum M = m - pairSum[i];
            int x = search(0, p, M);
            ans = max(ans, pairSum[i] + pairSum[x]);
        }
        cout << "Case " << caseNum + 1 << ": " << ans << "\n";
    }
    return 0;
}