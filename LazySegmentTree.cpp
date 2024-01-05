#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const int N = 5e5 + 10;
ll segment_tree[4 * N];
ll lazy[4 * N];
int arr[N];
void build(int id, int l, int r)
{
    // 1 Based
    lazy[id] = 0;
    if (l == r)
    {
        // leaf Node
        segment_tree[id] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    segment_tree[id] = segment_tree[2 * id] + segment_tree[2 * id + 1];
}
void propagate(int id, int l, int r)
{
    // Pass the lazy
    if (l != r)
    {
        // Avoiding Range Overflow
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
    }
    segment_tree[id] += (lazy[id] * (r - l + 1));
    lazy[id] = 0;
}
ll query(int id, int l, int r, int L, int R)
{
    propagate(id, l, r);
    // Recurse
    if (r < L || l > R)
    {
        // Disjoint
        return 0;
    }
    if (l >= L && r <= R)
    {
        // Inside Case
        return segment_tree[id];
    }
    int mid = (l + r) / 2;
    //  left child -> l to mid   and    right child -> mid+1 to r
    ll x = query(2 * id, l, mid, L, R);
    ll y = query(2 * id + 1, mid + 1, r, L, R);
    return x + y;
}
void update(int id, int l, int r, int L, int R, ll val)
{
    propagate(id, l, r);
    // Recurse
    if (r < L || l > R)
    {
        // Disjoint
        return;
    }
    if (l >= L && r <= R)
    {
        // Inside Case
        lazy[id] += val;
        propagate(id, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(2 * id, l, mid, L, R, val);
    update(2 * id + 1, mid + 1, r, L, R, val);
    segment_tree[id] = segment_tree[2 * id] + segment_tree[2 * id + 1];
    return;
}
void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    build(1, 1, n);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int u, v, w;
            cin >> u >> v >> w;
            update(1, 1, n, u, v, w);
        }
        else
        {
            int u;
            cin >> u;
            cout << query(1, 1, n, u, u) << endl;
        }
    }
}
int main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}
