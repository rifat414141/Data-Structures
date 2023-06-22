#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const int N = 2e5 + 10;
int segment_tree[4 * N];
int lazy[4 * N];
void create_tree(int arr[], int low, int high, int pos)
{
    if (low == high)
    {
        segment_tree[pos] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    create_tree(arr, low, mid, 2 * pos + 1);
    create_tree(arr, mid + 1, high, 2 * pos + 2);
    segment_tree[pos] = min(segment_tree[(2 * pos + 1)], segment_tree[(2 * pos + 2)]);
}
void update_segment_tree(int arr[], int index, int delta, int low, int high, int pos)
{
    if (index < low || index > high)
        return;
    if (low == high)
    {
        segment_tree[pos] += delta;
        return;
    }
    int mid = (low + high) / 2;
    update_segment_tree(arr, index, delta, low, mid, 2 * pos + 1);
    update_segment_tree(arr, index, delta, mid + 1, high, 2 * pos + 2);
    segment_tree[pos] = min(segment_tree[(2 * pos + 1)], segment_tree[(2 * pos + 2)]);
}
void update_index(int arr[], int index, int delta, int n)
{
    arr[index] += delta;
    update_segment_tree(arr, index, delta, 0, n - 1, 0);
}
void update_segment_tree_range(int arr[], int qlow, int qhigh, int delta, int low, int high, int pos)
{
    if (low > high || qlow > high || qhigh < low)
        return;
    if (low == high)
    {
        segment_tree[pos] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    update_segment_tree_range(arr, qlow, qhigh, delta, low, mid, 2 * pos + 1);
    update_segment_tree_range(arr, qlow, qhigh, delta, mid + 1, high, 2 * pos + 2);
    segment_tree[pos] = min(segment_tree[(2 * pos + 1)], segment_tree[(2 * pos + 2)]);
}
void update_range(int arr[], int qlow, int qhigh, int delta, int n)
{
    for (int i = qlow; i <= qhigh; ++i)
        arr[i] += delta;
    update_segment_tree_range(arr, qlow, qhigh, delta, 0, n - 1, 0);
}
int range_min_query(int qlow, int qhigh, int low, int high, int pos)
{
    if (qlow >= low && qhigh <= high)
    {
        return segment_tree[pos];
    }
    if (qhigh < low || qlow > high)
    {
        return INT_MAX;
    }
    int mid = (low + high) / 2;
    return min(range_min_query(qlow, qhigh, low, mid, 2 * pos + 1), range_min_query(qlow, qhigh, mid + 1, high, 2 * pos + 2));
}
void update_range_lazy(int qlow, int qhigh, int delta, int low, int high, int pos)
{
    if (low > high)
        return;
    if (lazy[pos] != 0)
    {
        segment_tree[pos] += lazy[pos];
        if (low != high)
        {
            lazy[(2 * pos + 1)] += lazy[pos];
            lazy[(2 * pos + 2)] += lazy[pos];
        }
        lazy[pos] = 0;
        if (qlow > high || qhigh < low)
            return;
        if (qlow <= low && qhigh >= high)
        {
            segment_tree[pos] += delta;
            if (low != high)
            {
                lazy[2 * pos + 1] += delta;
                lazy[2 * pos + 2] += delta;
            }
        }
        int mid = (low + high) / 2;
        update_range_lazy(qlow, qhigh, delta, low, mid, 2 * pos + 1);
        update_range_lazy(qlow, qhigh, delta, mid + 1, high, 2 * pos + 2);
        segment_tree[pos] = min(segment_tree[2 * pos + 1], segment_tree[2 * pos + 1]);
    }
}
int range_minimum_query_lazy(int qlow, int qhigh, int low, int high, int pos)
{
    if(low>high) return INT_MAX;
    if (lazy[pos] != 0)
    {
        segment_tree[pos] += lazy[pos];
        if (low != high)
        {
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(qlow>high || qhigh<low) return INT_MAX;
    if(qlow<=low && qhigh>=high){
        return segment_tree[pos];
    }
    int mid = (low+high)/2;
    return min(range_minimum_query_lazy(qlow, qhigh, low, mid, 2*pos+1), range_minimum_query_lazy(qlow, qhigh, mid+1, high, 2*pos+2));
}
int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    create_tree(arr, 0, n - 1, 0);
    return 0;
}