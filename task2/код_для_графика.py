import matplotlib.pyplot as plt
import numpy as np

# Вставьте сюда вывод из C++ программы
N_values = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000]
brute_force_times = [66, 500, 759, 1001, 1569, 2229, 3037, 3945, 4978, 6161, 7377, 8773, 10281, 11782, 13513]
optimized_times = [184, 519, 510, 651, 775, 932, 1089, 1262, 1430, 1535, 1699, 1872, 2005, 2157, 2345]            # Пример данных

# Создаем фигуру с двумя графиками
plt.figure(figsize=(14, 6))

# Первый график - линейный масштаб
plt.subplot(1, 2, 1)
plt.plot(N_values, brute_force_times, 'ro-', label='Полный перебор (O(N²))')
plt.plot(N_values, optimized_times, 'bo-', label='Оптимизированный (O(N))')
plt.xlabel('Размер массива (N)')
plt.ylabel('Время (мс)')
plt.title('Сравнение времени работы')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
