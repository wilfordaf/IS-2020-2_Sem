import matplotlib.pyplot as plt
import math as math


def maxlenofthrow(v0, alpha):
    return ((v0 ** 2) * math.sin(2 * alpha)) / 9.83


def maxheightofthrow(v0, alpha):
    return ((v0 ** 2) * (math.sin(alpha)) ** 2) / 19.63


# пусть начальная скорость 10 м/c ; построим график для всех углов в диапазоне 0 <= alpha <= 90 с шагом 1
L, H = [], []
for i in range(91):
    a = math.radians(i)
    L.append(maxlenofthrow(10, a))
    H.append(maxheightofthrow(10, a))

plt.title("Максимальная высота и дальность полёта при v = 10 м/c - const")
plt.xlabel("Максимальная высота")
plt.ylabel("Максимальная дальность")
plt.plot(H, L)
plt.show()
