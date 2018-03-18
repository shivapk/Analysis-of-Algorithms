/*
 * For reference - http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/Dynamic/activitydyn.htm
 */
#include <iostream>
#include <vector>
using namespace std;
int activity_selection(vector<vector<int> > activities);
bool myComparator(const vector<int> &vec1, const vector<int>  &vec2);
int custom_binary_search(vector<vector<int> > activities, int index);
void print_results(vector<int> results);
int main(int argc, char *argv[])
{
    int num_activities;
    cout << "enter no of activities" << endl;
    cin >> num_activities;
    vector<vector<int> > activities(num_activities, vector<int>(2, 0));

    for (int i = 0; i < num_activities; i++)
    {
        int start_time, end_time;
        cout << "enter starting and end time of activities: " << i + 1 << endl;
        cin >> start_time >> end_time;
        activities[i][0] = start_time;
        activities[i][1] = end_time;
    }
    /*cout << "original:" << endl;
    for (int i = 0; i < num_activities; i++)
    {
        cout << activities[i][0] << " " << activities[i][1] << endl;
    }
    */
    sort(activities.begin(), activities.end(), myComparator);
    /*cout << "after sorting:" << endl;
    for (int i = 0; i < num_activities; i++)
    {
        cout << activities[i][0] << " " << activities[i][1] << endl;
    }
    */
    cout << endl;
    cout << "max num of compatible activities : " << activity_selection(activities) << endl;
}
bool myComparator(const vector<int> &vec1, const vector<int>  &vec2)
{
    if (vec1[1] < vec2[1])
        return true;
    else 
        return false;
}
int custom_binary_search(vector<vector<int> > activities, int index)
{
    int chosen_starting_time = activities[index][0];
    int i = 0, j = index - 1, mid = -1;
    while (i <= j)
    {
        mid = (i + j)/2;
        if (activities[mid][1] <= chosen_starting_time && chosen_starting_time < activities[mid + 1][1])
            break;
        else if (chosen_starting_time >= activities[mid][1])
            i = mid + 1;
        else
            j = mid - 1;
    }
    if (i <= j)
        return mid;
    else
        return -1;

}
int activity_selection(vector<vector<int> > activities)
{
    int num_activities = activities.size();
    vector<int> results_elements(num_activities, -1);
    vector<int> results(num_activities, 0);
    results[0] = 1;
    results_elements[0] = 0;
    for (int index = 1; index < num_activities; index++)
    {
        int result1 = results[index - 1];
        int result2 = 0;
        int found_compatible_index = custom_binary_search(activities, index);
        if (found_compatible_index != -1)
        {
            result2 = 1 + results[found_compatible_index];
        }
           
        results[index] = max(result1, result2);
        if (max(result1, result2) ==  result2)
            results_elements[index] = found_compatible_index;
    }
    //return results[num_activities - 1];
    print_results(results_elements);
    return results[num_activities - 1];
}
void print_results(vector<int> results)
{
    int index = results.size() - 1;
    while (index >= 0)
    {
        if (results[index] != -1)
        {
            cout << index + 1<< " ";
            index = results[index];
            if (index == 0)
                break;
        }
        else
            index--;
    }
    cout << endl;
}
