#include <iostream>

using namespace std;

/*
    first lab, task 33 (with two-dimension arrays)
*/

int main()
{
    int n;
    cout << "Enter the size(n): ";
    cin >> n;
    int **a = new int*[n];
    for (int i = 0; i < n; ++i)
        *(a+i) = new int[n];

    cout << "Input your array row-by-row. Put here " << n << " number is a line\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "a[" << i << "]: ";
        for (int j = 0; j < n; ++j)
            cin >> *(*(a+i)+j);
    }

    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            sum += *(*(a+i)+j);

    cout << sum << endl;

    return 0;
}