#include <iostream>
#include <vector>
using namespace std;
//basic recursion
int max_profit_recursive(int *p, int n, int &count);
// top down with dp(memoization)
int top_down_memoization(int *p, int n, int &count, int *memo);
// bottom up 
int bottom_up_dp(int *p, int n, int *saved_splits);
// printing solution 
void print_results(int *saved_splits, int len);
int main(int argc, char *argv[])
{
    int p[] = {1, 5, 8, 9, 10, 18, 20, 24, 30};
    vector<int> prices(p, p + sizeof(p)/sizeof(int));
    int len = sizeof(p)/sizeof(int);
    len = 4;
    int count = 0;
    cout << "basic_recursion ==> " << endl;
    cout << "max profit : " << max_profit_recursive(p, len, count) << endl;
    cout << "no of calls : " << count << endl;

    cout << "top down memoization ==> " << endl;
    int *memo = new int[len];
    for (int i = 0; i < len; i++)
        memo[i] = -1;
    count = 0;
    cout << "max profit : " << top_down_memoization(p, len, count, memo) << endl;
    cout << "no of calls : " << count << endl;
    delete[] memo;
       

    cout << "bottom up dp ==> " << endl;
    int *saved_splits = new int[len + 1];
    cout << "max profit : " << bottom_up_dp(p, len, saved_splits) << endl;
    cout << "splits : " << endl;
    print_results(saved_splits, len);
}

int max_profit_recursive(int *p, int n, int &count)
{
    (count)++;
    if (n == 0)
        return 0;
    int q =-1;
    for (int i = 1; i <= n; i++)
    {
        q = max(q, p[i - 1] + max_profit_recursive(p, n - i, count));
    }
    return q;
}

int top_down_memoization(int *p, int n, int &count, int *memo)
{
    (count)++;
    if (n == 0)
        return 0;
    if (memo[n - 1] != -1)
        return memo[n - 1];
    int q = -1;
    for (int i = 1; i <= n; i++)
    {
        q = max(q, p[i - 1] + top_down_memoization(p, n - i, count, memo));
    }
    memo[n - 1] = q;
    return q;

}

int bottom_up_dp(int *p, int n, int *saved_splits)
{
    int *saved_results = new int[n + 1];
    saved_results[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int q = -1, x = -1;
        for (int j = 1; j <= i; j++)
        {
            //q = max(q, p[j - 1] + saved_results[i - j]);
            int temp = p[j - 1] + saved_results[i - j];
            if (temp > q)
            {
                q = temp;
                x = j;
            }
        }
        saved_results[i] = q;
        saved_splits[i] = x;
    }
    int ans = saved_results[n];
    delete[] saved_results;
    return ans;
}

void print_results(int *saved_splits, int n)
{
    while (n > 0)
    {
        cout << saved_splits[n] << " ";
        n = n - saved_splits[n];
    }
}
