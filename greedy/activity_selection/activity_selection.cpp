#include <iostream>
#include <vector>
using namespace std;
bool custom_comparator(const vector<int> &vec1, const vector<int> &vec2)
{
    if (vec1[1] < vec2[1])
        return true;
    else if (vec1[1] == vec2[1])
    {
        if (vec1[0] <= vec2[0]) 
            return true;
        else
            return false;
    }
    else
        return false;
}
struct myCompare
{
    bool operator() (const vector<int> &vec1, const vector<int> &vec2)
    {
        if (vec1[1] < vec2[1])
            return true;
        else if (vec1[1] == vec2[1])
        {
            if (vec1[0] <= vec2[0]) 
                return true;
            else
                return false;
        }
        else
            return false;

    }
}foo;
void activity_selection_recursive(vector<vector<int> > activities, int finish_time, int index, vector<int> &result)
{
    while(index < activities.size() && activities[index][0] < finish_time)
        index++;
    if (index == activities.size())
        return;
    result.push_back(index + 1);
    activity_selection_recursive(activities, activities[index][1], index + 1, result);
}

vector<int> activity_selection_iterative(vector<vector<int> > activities)
{
    vector<int> result;
    int index = 0, finish_time = 0, count = 0;
    while (index < activities.size())
    {
        if (activities[index][0] >= finish_time)
        {
            finish_time = activities[index][1];
            result.push_back(index + 1);
            count++;
        }
        index++;
    }
    //return count;
    return result;
}
int main(int argc, char *argv[])
{
    int num_activities;
    cout << "enter num of activities : " << endl;
    cin >> num_activities;
    vector<vector<int> > activities(num_activities,  vector<int>(2, 0));
    for (int i = 1; i <= num_activities; i++)
    {
        cout << "enter starting and ending times of activity " << i << endl;
        cin >> activities[i - 1][0] >> activities[i - 1][1];
    }
    // sorting by finishing times
    //sort(activities.begin(), activities.end(), custom_comparator);
    sort(activities.begin(), activities.end(), foo);
    vector<int> result;
    //cout << "recursive - maximum #compatible activities : " << activity_selection_recursive(activities, 0, 0, result) << endl;
    activity_selection_recursive(activities, 0, 0, result);
    cout << "recursive - maximum #compatible activities : " << result.size() << endl;
    cout << "activities are : ";
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    result = activity_selection_iterative(activities);
    cout << endl << "iterative - maximum #compatible activities : " << result.size() << endl;
    cout << endl << "activities are : ";
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;
}
