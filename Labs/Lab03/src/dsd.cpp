#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of values: ";
    cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) {
        cout << "Enter value " << i + 1 << " : ";
        cin >> *(arr + i);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                int temp       = *(arr + j);
                *(arr + j)     = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }

    double Mean, Median;
    int    Mode = -1;

    double *mean   = &Mean;
    double *median = &Median;
    int    *mode   = &Mode;

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *(arr + i);
    }

    *mean = sum / n;

    if (n % 2 == 0) {
        *median = (*(arr + (n / 2 - 1)) + *(arr + (n / 2))) / 2.0;
    } else {
        *median = *(arr + (n / 2));
    }

    int max = 0;
    *mode   = -1;
    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (*(arr + j) == *(arr + i)) {
                count++;
            }
        }
        if (count > max) {
            max   = count;
            *mode = *(arr + i);
        }
    }

    // Checking if mean, mesian, mode are present in array
    bool mean_present = false;
    for (int i = 0; i < n; i++) {
        if (*mean == *(arr + i)) {
            mean_present = true;
            break;
        }
    }

    bool median_present = false;
    for (int i = 0; i < n; i++) {
        if (*median == *(arr + i)) {
            median_present = true;
            break;
        }
    }

    bool mode_present = false;
    if (max > 1) {
        mode_present = true;
    }

    cout << "Mean: " << *mean;
    if (mean_present) {
        cout << " (present)" << endl;
    } else {
        cout << " (not present)" << endl;
    }

    cout << "Median: " << *median;
    if (median_present) {
        cout << " (present)" << endl;
    } else {
        cout << " (not present)" << endl;
    }

    cout << "Mode: ";
    if (mode_present) {
        cout << *mode << " (present)" << endl;
    } else {
        cout << "None (not present)" << endl;
    }

    return 0;
}