#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
class input;
input* huffman(vector<input *> entries);
class input
{
    public:
        char c;
        int freq;
        input *left, *right;
        string codeword;
};
struct myComparison
{
    bool operator()(const input *lhs, const input *rhs)
    {
        return lhs->freq > rhs->freq;
    }
};

void get_codeword(input *root, string str)
{
    if (!root)
        return;
    if (root->c != '$')
        cout << "codeword for char : " << root->c << " " << str << endl;
    get_codeword(root->left, str + "0");
    get_codeword(root->right, str + "1");
}
int main(int argc, char *argv[])
{
    int num;
    vector<input *> entries;
    cout << "enter num of chars" << endl;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        int freq;
        char ch;
        cout << "enter char and its freq " << endl;
        cin >> ch >> freq;
        input *foo = new input(); 
        foo->c = ch;
        foo->freq = freq;
        entries.push_back(foo);
    }
    input *root = huffman(entries);
    string str;
    get_codeword(root, str);
}
input* huffman(vector<input *> entries)
{
    priority_queue<input *, vector<input *>, myComparison> pq;
    for (input *ip: entries)
        pq.push(ip);

    int i = 1, num = entries.size();
    while (i < num)
    {
        input *input1 = pq.top();
        pq.pop();
        input *input2 = pq.top();
        pq.pop();
        input *foo = new input();
        foo->freq = input1->freq + input2->freq;
        foo->c = '$';
        foo->left = input1;
        foo->right = input2;
        pq.push(foo);
        i++;
    }
    input *root = pq.top();
    return root;
}
