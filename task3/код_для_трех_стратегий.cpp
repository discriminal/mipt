#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

// Стратегия A: переместить найденный элемент в начало
int linearSearchStrategyA(int arr[], int size, int key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            if (i != 0) {
                std::swap(arr[i], arr[0]);
            }
            return i;
        }
    }
    return -1;
}

// Стратегия B: поменять местами с предыдущим элементом
int linearSearchStrategyB(int arr[], int size, int key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            if (i != 0) {
                std::swap(arr[i], arr[i - 1]);
            }
            return i;
        }
    }
    return -1;
}

// Стратегия C: учитываем счетчики обращений
int linearSearchStrategyC(int arr[], int size, int key, int counters[]) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            counters[i]++;
            // Продвигаем элемент вверх, если его счетчик больше предыдущего
            if (i > 0 && counters[i] > counters[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                std::swap(counters[i], counters[i - 1]);
                i--;
            }
            return i;
        }
    }
    return -1;
}


int main() {
    const int test_sizes[] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000 };
    const int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
    const int repeats = 1000;
    const int search_repeats = 100;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Вывод размеров массивов для Python 
    std::cout << "sizes = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << test_sizes[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n\n";

    // Массивы для хранения результатов
    long stratA_uniform[num_tests];
    long stratB_uniform[num_tests];
    long stratC_uniform[num_tests];
    long stratA_biased[num_tests];
    long stratB_biased[num_tests];
    long stratC_biased[num_tests];

    for (int i = 0; i < num_tests; ++i) {
        int size = test_sizes[i];
        int* arr = new int[size];
        int* counters = new int[size]();

        // Заполняем массив уникальными значениями
        for (int j = 0; j < size; ++j) {
            arr[j] = j;
        }

        // Перемешиваем массив
        std::shuffle(arr, arr + size, gen);

        // Создаем копии для каждой стратегии
        int* arrA = new int[size];
        int* arrB = new int[size];
        int* arrC = new int[size];
        std::copy(arr, arr + size, arrA);
        std::copy(arr, arr + size, arrB);
        std::copy(arr, arr + size, arrC);

        // 1. Тест равномерного распределения запросов
        std::uniform_int_distribution<int> uniform_dist(0, size - 1);

        // Стратегия A
        auto start = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            for (int s = 0; s < search_repeats; ++s) {
                int key = uniform_dist(gen);
                linearSearchStrategyA(arrA, size, key);
            }
        }
        auto end = std::chrono::steady_clock::now();
        stratA_uniform[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Стратегия B
        start = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            for (int s = 0; s < search_repeats; ++s) {
                int key = uniform_dist(gen);
                linearSearchStrategyB(arrB, size, key);
            }
        }
        end = std::chrono::steady_clock::now();
        stratB_uniform[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Стратегия C
        start = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            for (int s = 0; s < search_repeats; ++s) {
                int key = uniform_dist(gen);
                linearSearchStrategyC(arrC, size, key, counters);
            }
        }
        end = std::chrono::steady_clock::now();
        stratC_uniform[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // 2. Тест неравномерного распределения (20% элементов откуда-то из середины массива запрашиваются 80% времени)
        std::uniform_int_distribution<int> biased_dist(size / 5 - 1, 2*(size / 5 - 1));

        // Сброс массивов и счетчиков
        std::copy(arr, arr + size, arrA);
        std::copy(arr, arr + size, arrB);
        std::copy(arr, arr + size, arrC);
        std::fill(counters, counters + size, 0);

        // Стратегия  откуда-то из середины
        start = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            for (int s = 0; s < search_repeats; ++s) {
                int key = (s % 5 == 0) ? uniform_dist(gen) : biased_dist(gen); //Каждый 5-й запрос (20%) выбирает случайный элемент из всего массива uniform_dist, Остальные 80 % запросов выбирают элементы только из первых 20 % массива biased_dist
                linearSearchStrategyA(arrA, size, key);
            }
        }
        end = std::chrono::steady_clock::now();
        stratA_biased[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Стратегия B
        start = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            for (int s = 0; s < search_repeats; ++s) {
                int key = (s % 5 == 0) ? uniform_dist(gen) : biased_dist(gen);
                linearSearchStrategyB(arrB, size, key);
            }
        }
        end = std::chrono::steady_clock::now();
        stratB_biased[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Стратегия C
        start = std::chrono::steady_clock::now();
        for (int r = 0; r < repeats; ++r) {
            for (int s = 0; s < search_repeats; ++s) {
                int key = (s % 5 == 0) ? uniform_dist(gen) : biased_dist(gen);
                linearSearchStrategyC(arrC, size, key, counters);
            }
        }
        end = std::chrono::steady_clock::now();
        stratC_biased[i] = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        delete[] arr;
        delete[] arrA;
        delete[] arrB;
        delete[] arrC;
        delete[] counters;
    }

    // Вывод результатов для равномерного распределения
    std::cout << "stratA_uniform = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << stratA_uniform[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n";

    std::cout << "stratB_uniform = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << stratB_uniform[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n";

    std::cout << "stratC_uniform = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << stratC_uniform[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n\n";

    // Вывод результатов для неравномерного распределения
    std::cout << "stratA_biased = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << stratA_biased[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n";

    std::cout << "stratB_biased = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << stratB_biased[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n";

    std::cout << "stratC_biased = [";
    for (int i = 0; i < num_tests; ++i) {
        std::cout << stratC_biased[i] << (i < num_tests - 1 ? ", " : "");
    }
    std::cout << "]\n";

  
}
