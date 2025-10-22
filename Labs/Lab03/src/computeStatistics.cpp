#include <iostream>

double find_mean(int arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += *(arr + i);
    }
    return sum / n;
}

double find_median(int arr[], int n) {
    if (n % 2 == 0) {
        return (*(arr + (n / 2 - 1)) + *(arr + (n / 2))) / 2.0;
    } else {
        return *(arr + (n / 2));
    }
}

int find_mode(int arr[], int n) {
    int maxCount = 0, mode = -1;

    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (*(arr + j) == *(arr + i)) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mode     = *(arr + i);
        }
    }

    if (maxCount > 1) return mode;
    return -1;  // no mode
}

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                int temp       = *(arr + j);
                *(arr + j)     = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter number of values: ";
    std::cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        std::cout << "Enter value " << i + 1 << " : ";
        std::cin >> *(arr + i);
    }

    sort_array(arr, n);
    double mean   = find_mean(arr, n);
    double median = find_median(arr, n);
    int    mode   = find_mode(arr, n);

    bool mean_present = false;
    if (mean == (int)mean) {
        for (int i = 0; i < n; i++) {
            if ((int)mean == *(arr + i)) {
                mean_present = true;
                break;
            }
        }
    }

    bool median_present = false;
    if (median == (int)median) {
        for (int i = 0; i < n; i++) {
            if ((int)median == *(arr + i)) {
                median_present = true;
                break;
            }
        }
    }

    bool mode_present = false;
    if (mode != -1) {
        for (int i = 0; i < n; i++) {
            if (mode == *(arr + i)) {
                mode_present = true;
                break;
            }
        }
    }

    std::cout << "Mean: " << mean;
    if (mean_present) {
        std::cout << " (present)" << std::endl;
    } else {
        std::cout << " (not present)" << std::endl;
    }

    std::cout << "Median: " << median;
    if (median_present) {
        std::cout << " (present)" << std::endl;
    } else {
        std::cout << " (not present)" << std::endl;
    }

    std::cout << "Mode: ";
    if (mode_present) {
        std::cout << mode << " (present)" << std::endl;
    } else {
        std::cout << "None (not present)" << std::endl;
    }

    return 0;
}
