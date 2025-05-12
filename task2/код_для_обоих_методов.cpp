#include <iostream>
#include <chrono>
#include <algorithm> // для std::sort

// Функция полного перебора (O(N2))
bool findSumBruteForce(int arr[], int size, int target, int& index1, int& index2) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] + arr[j] == target) {
                index1 = i;
                index2 = j;
                return true;
            }
        }
    }
    return false;
}

// Функция для отсортированного массива (O(N))
bool findSumOptimized(int arr[], int size, int target, int& index1, int& index2) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            index1 = left;
            index2 = right;
            return true;
        }
        else if (sum < target) {
            left++;
        }
        else {
            right--;
        }
    }
    return false;
}

int main() {
    // Размеры массивов для тестирования
    const int test_sizes[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000};
    const int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);

    // Количество повторений для каждого теста
    const int repeats = 50;

    // Для хранения результатов
    long brute_force_times[num_tests];
    long optimized_times[num_tests];


    for (int i = 0; i < num_tests; ++i) {
        int size = test_sizes[i];
        int* arr = new int[size];

        // Заполнение массива случайными числами
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 10000;
        }

        // Для оптимизированного алгоритма массив должен быть отсортирован
        std::sort(arr, arr + size);

        // Целевая сумма (гарантированно не существует в массиве)
        int target = 20000;

        // Тестирование полного перебора
        auto begin = std::chrono::steady_clock::now();
        int index1, index2;
        for (int cnt = 0; cnt < repeats; ++cnt) {
            findSumBruteForce(arr, size, target, index1, index2);
        }
        auto end = std::chrono::steady_clock::now();
        brute_force_times[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << brute_force_times[i] << std::endl;

        // Тестирование оптимизированного алгоритма
        begin = std::chrono::steady_clock::now();
        for (int cnt = 0; cnt < repeats*1000; ++cnt) {
            findSumOptimized(arr, size, target, index1, index2);
        }
        end = std::chrono::steady_clock::now();
        optimized_times[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << optimized_times[i] << std::endl;

        delete[] arr;
    }

    // Вывод результатов в формате для Python
    std::cout << "N_values = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << test_sizes[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;

    std::cout << "brute_force_times = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << brute_force_times[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;

    std::cout << "optimized_times = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << optimized_times[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;

    return 0;
}
