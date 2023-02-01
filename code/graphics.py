import matplotlib.pyplot as plt
import numpy as np

f = open('measute.txt', 'r')
A = []
B = []

for line in f:
	k = line.find(" ")
	A.append(float(line[0: k]))
	B.append(float(line[k:]))

print(A)
print(B)
plt.plot(B, A, label = "Генерация изображения")
plt.grid(True)
plt.title('')

plt.legend()
plt.scatter(B, A, color='blue', s=20)
plt.ylabel('Время (мс)')
plt.xlabel('Количество точек')
plt.savefig('graph.png')
plt.show()

f.close()
