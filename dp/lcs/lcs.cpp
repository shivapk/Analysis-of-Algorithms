/*
 *Here we start looking from the end , i.e. to find C(m,n)
 *C(i,j) = 0 if i = 0 || j = 0
 *       = C(i - 1, j - 1) + 1 if x[i] == y[j]
 *       = max(C(i - 1, j), C(i, j - 1)) if x[i] != y[j]
 */


#include <iostream>
#include <string>
#include <vector>
using namespace std;
int recursive(string str1, string str2, int i, int j);
int recursive_memoization(string str1, string str2, int i, int j, vector<vector<int> > &memo);
int bottom_up(string str1, string str2);
void printLcs(string str1, string str2, vector<vector<int> > signs);
int main(int argc, char *argv[])
{
    //string str1 = "actgggtaccatga";
    //string str2 = "actgagtacaatga";
    string str1 = "abcabda";
    string str2 = "bacdba";
    cout << "lcs length : " << recursive(str1, str2, str1.size(), str2.size()) << endl;
    vector<vector<int> > memo(str1.size() + 1, vector<int>(str2.size() + 1, -1));
    cout << "memoization - lcs length : " << recursive_memoization(str1, str2, str1.size(), str2.size(), memo) << endl;
    cout << "bottom up - lcs length : " << bottom_up(str1, str2) << endl;
}

int recursive(string str1, string str2, int i, int j)
{
    if (i == 0 || j == 0)
        return 0;
    else if (str1[i - 1] == str2[j - 1])
        return (recursive(str1, str2, i - 1, j - 1) + 1);
    else
        return (max(recursive(str1, str2, i - 1, j), recursive(str1, str2, i, j - 1)));
}

int recursive_memoization(string str1, string str2, int i, int j, vector<vector<int> > &memo)
{
    if (i == 0 || j == 0)
        return 0;
    else if (memo[i][j] != -1)
        return memo[i][j];
    else if (str1[i - 1] == str2[j - 1])
    {
        memo[i][j] = recursive_memoization(str1, str2, i - 1, j - 1, memo) + 1;
        return memo[i][j];
    }
    else
    {
        memo[i][j] = max(recursive_memoization(str1, str2, i - 1, j, memo), recursive_memoization(str1, str2, i, j - 1, memo));
        return memo[i][j];
    }
}

int bottom_up(string str1, string str2)
{
    int m = str1.size();
    int n = str2.size();
    vector<vector<int> > results(m + 1, vector<int>(n + 1, 0));
    vector<vector<int> > signs(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (str1[i] == str2[j])
            {
                results[i][j] = results[i - 1][j - 1] + 1;
                signs[i][j] = 1;
            }
            else if (results[i - 1][j] > results[i][j - 1])
            {
                results[i][j] = results[i - 1][j];
                signs[i][j] = 2;
            }
            else
            {
                results[i][j] = results[i][j - 1];
                signs[i][j] = 3;
            }
        }
    }
    cout << endl;
    printLcs(str1, str2, signs);
    return results[m][n];
}
void printLcs(string str1, string str2, vector<vector<int> > signs)
{
   int x = str1.size(), y = str2.size();
   cout << "str1 : " << x << " str2 : " << y << endl; 
   while (x > 0 && y > 0)
   {
       if (signs[x][y] == 1)
       {
           cout << str1[x - 1] <<  " ";
           x -= 1;
           y -= 1;
       }
       else if(signs[x - 1][y] > signs[x][y - 1])
       {
           x -= 1;
       }
       else
       {
           y -= 1;
       }
   }
}
