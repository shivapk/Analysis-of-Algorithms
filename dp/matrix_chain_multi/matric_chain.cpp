#include <iostream>
#include <vector>
using namespace std;
void print_optimal_parens(vector<vector<int> > brackets, int i, int j);
int bottom_up(vector<int> sizes);
int recursive(vector<int> sizes, int i, int j);
int top_down_memoization(vector<int> sizes, int i, int j, vector<vector<int> > &memo);
int main(int argc, char *argv[])
{
    int p[] = {10, 100, 5, 50};
    vector<int> matrix_sizes(p, p + sizeof(p)/sizeof(int));
    cout <<  "bottom up -> best way to multiply : " << bottom_up(matrix_sizes) << endl;
    cout << "recursive -> " << recursive(matrix_sizes, 1, matrix_sizes.size() - 1) << endl;

    vector<vector<int> > memo(matrix_sizes.size(), vector<int>(matrix_sizes.size(), 0));
    cout << "top down memoization -> " << top_down_memoization(matrix_sizes, 1, matrix_sizes.size() - 1, memo) << endl;

}

int recursive(vector<int> sizes, int i, int j)
{
    if (i == j)
        return 0;
    int cost, min_cost = INT_MAX;
    for (int k = i; k < j; k++)
    {
        cost = recursive(sizes, i, k) + recursive(sizes, k + 1, j) + sizes[i - 1]*sizes[k]*sizes[j];
        if (cost < min_cost)
            min_cost = cost;
    }
    return min_cost;
}

int top_down_memoization(vector<int> matrix_sizes, int i, int j, vector<vector<int> > &memo)
{
    int cost, min_cost = INT_MAX;
    if (i == j)
        return 0;
    if (memo[i][j] != 0)
        return memo[i][j];
    for (int k = i; k < j; k++)
    {
        cost = top_down_memoization(matrix_sizes, i, k, memo) + top_down_memoization(matrix_sizes, k + 1, j, memo) + matrix_sizes[i - 1]*matrix_sizes[k]*matrix_sizes[j];
        if (cost < min_cost)
            min_cost = cost;
    }
    memo[i][j] = min_cost;
    return min_cost;
}

int bottom_up(vector<int> sizes)
{
    int num_matrices = sizes.size() - 1;
    vector<vector<int> > results(num_matrices + 1, vector<int>(num_matrices + 1, 0));
    vector<vector<int> > brackets(num_matrices + 1, vector<int>(num_matrices + 1, 0));
    for (int i = 1; i <= num_matrices; i++)
    {
        results[i][i] = 0;
    }
    for (int length = 2; length <= num_matrices; length++)
    {
        for (int i = 1; i <= num_matrices - length + 1; i++)
        {
            int j = i + length - 1;
            int min_cost = INT_MAX;
            int pos = -1;
            for (int k = i; k < j; k++)
            {
                int cost = results[i][k] + results[k + 1][j] + sizes[i - 1]*sizes[k]*sizes[j];
                if (cost < min_cost)
                {
                    min_cost = cost;
                    pos = k;
                }
            }
            results[i][j] = min_cost;
            brackets[i][j] = pos;
        }
    }
    print_optimal_parens(brackets, 1, num_matrices);
    cout << endl;
    return results[1][num_matrices];
}

void print_optimal_parens(vector<vector<int> > brackets, int i, int j)
{
    if (i == j)
        cout << "A" << i;
    else
    {
        cout << "(";
        print_optimal_parens(brackets, i, brackets[i][j]);
        print_optimal_parens(brackets, brackets[i][j] + 1, j);
        cout << ")";
    }
}
