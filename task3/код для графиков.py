import matplotlib.pyplot as plt
import numpy as np

sizes = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000]

stratA_uniform = [112, 215, 309, 395, 496, 589, 682, 778, 884, 969, 1073, 1155, 1283, 1350, 1447]
stratB_uniform = [104, 208, 315, 403, 495, 581, 685, 786, 888, 980, 1073, 1164, 1259, 1365, 1448]
stratC_uniform = [108, 211, 307, 419, 502, 588, 683, 785, 891, 967, 1065, 1202, 1259, 1363, 1471]

stratA_biased = [117, 205, 334, 398, 491, 593, 686, 779, 880, 988, 1062, 1157, 1279, 1351, 1470]
stratB_biased = [85, 201, 304, 397, 496, 578, 686, 772, 872, 967, 1088, 1162, 1259, 1332, 1450]
stratC_biased = [90, 196, 306, 400, 504, 595, 696, 776, 879, 977, 1097, 1186, 1270, 1333, 1465]

# Настройка стиля графиков
plt.figure(figsize=(14, 6))

# График для равномерного распределения
plt.subplot(1, 2, 1)
plt.plot(sizes, stratA_uniform, 'o-', color='royalblue', label='Стратегия A')
plt.plot(sizes, stratB_uniform, 's-', color='darkorange', label='Стратегия B')
plt.plot(sizes, stratC_uniform, '^-', color='forestgreen', label='Стратегия C')
plt.xlabel('Размер массива', fontsize=12)
plt.ylabel('Время (мс)', fontsize=12)
plt.title('Равномерное распределение запросов', fontsize=14)
plt.legend(fontsize=12)
plt.grid()

# График для неравномерного распределения
plt.subplot(1, 2, 2)
plt.plot(sizes, stratA_biased, 'o-', color='royalblue', label='Стратегия A')
plt.plot(sizes, stratB_biased, 's-', color='darkorange', label='Стратегия B')
plt.plot(sizes, stratC_biased, '^-', color='forestgreen', label='Стратегия C')
plt.xlabel('Размер массива', fontsize=12)
plt.ylabel('Время (мс)', fontsize=12)
plt.title('Неравномерное распределение запросов', fontsize=14)
plt.legend(fontsize=12)
plt.grid()

plt.tight_layout()
plt.show()
