#include <cstring>
#include <iostream>
#include <string>

void sortStrings(char* arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char* str1 = arr[i];
            char* str2 = arr[j];

            int com = strcmp(arr[i], arr[j]);
            if (com > 0) {
                char* temp = arr[i];
                arr[i]     = arr[j];
                arr[j]     = temp;
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter number of strings: ";
    std::cin >> n;
    char* arr[n];

    std::cin.ignore();
    for (int i = 0; i < n; i++) {
        char* name = new char[100];
        std::cout << "Enter string " << i + 1 << " ";
        std::cin.getline(name, 100);
        arr[i] = name;
    }

    sortStrings(arr, n);

    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << std ::endl;
    }

    return 0;
}