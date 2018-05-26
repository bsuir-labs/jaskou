#include <iostream>

using namespace std;

int main()
{
    int N;
    cout << "Size if the first array: ";
    cin >> N;
    int *a = new int[N];
    for (int i = 0; i < N; ++i)
    {
        cout << "A[" << i << "] = ";
        cin >> *(a+i);
    }

    cout << "Size of the second array: ";
    int M;
    cin >> M;
    int *b = new int[M];
    for (int i = 0; i < M; ++i)
    {
        cout << "B[" << i << "] = ";
        cin >> *(b + i);
    }

    int positives1 = 0, positives2 = 0;

    for (int i = 0; i < N; ++i)
        positives1 += int(*(a+i) > 0);
    for (int i = 0; i < M; ++i)
        positives2 += int(*(b+i) > 0);

    if (positives2 < positives1)
    {
        cout << "B: ";
        for (int i = 0; i < M; ++i)
            cout << *(b+i) << " ";
        cout << "\nA: ";
        for (int i = 0; i < N; ++i)
            cout << *(a + i) << " ";
        cout << endl;
    } else {
        cout << "A: ";
        for (int i = 0; i < N; ++i)
            cout << *(a + i) << " ";
        cout << endl;
        cout << "B: ";
        for (int i = 0; i < M; ++i)
            cout << *(b+i) << " ";
        cout << endl;
    }

    return 0;
}