#include <bits/stdc++.h>
using namespace std;
#define ll long long int
ll modInv(ll A, ll M)
{
    ll m0 = M;
    ll y = 0, x = 1;
    if (M == 1)
        return 0;
    while (A > 1)
    {
        int q = A / M;
        int t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}
ll CRT(vector<pair<ll, ll>> &v)
{
    ll prod = 1;
    for (int i = 0; i < v.size(); ++i)
        prod *= v[i].first;

    ll ans = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        ll pp = prod / v[i].first;
        ll inv = modInv(pp, v[i].first);
        if (inv < 0)
            inv += v[i].first;
        ans += v[i].second * pp * inv;
        ans %= prod;
    }

    return ans;
}
