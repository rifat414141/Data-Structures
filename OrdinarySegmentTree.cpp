#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const int N = 2e5 + 10;
int arr[N];
ll segment_tree[4 * N];
void build(int id, int l, int r)
{
    if (l == r)
    {
        segment_tree[id] = arr[l - 1];
        return;
    }
    // left child -> l to mid and right child -> mid+1 to r
    int mid = (l + r) / 2;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    segment_tree[id] = segment_tree[2 * id] + segment_tree[2 * id + 1];
    return;
}
void update(int id, int l, int r, int i, int val)
{
    // 1 Based index
    if (l == r)
    {
        // Base condition
        segment_tree[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    // left child -> l to mid and right child -> mid+1 to r
    if (i <= mid)
        update(2 * id, l, mid, i, val);
    else
        update(2 * id + 1, mid + 1, r, i, val);
    segment_tree[id] = segment_tree[2 * id] + segment_tree[2 * id + 1];
    return;
}
ll range(int id, int l, int r, int L, int R)
{
    // l and r (for current index)
    if (R < l || L > r)
    {
        // disjoint
        return 0;
    }
    if (L <= l && r <= R)
    {
        // complete overlapping
        return segment_tree[id];
    }
    int mid = (l + r) / 2;
    // left child -> l to mid and right child -> mid+1 to r
    ll x = range(2 * id, l, mid, L, R);
    ll y = range(2 * id + 1, mid + 1, r, L, R);
    return x + y;
}
void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }
    build(1, 1, n);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int i, val;
            cin >> i >> val;
            update(1, 1, n, i, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << range(1, 1, n, l, r) << endl;
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
