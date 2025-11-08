import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

k = 50

img = Image.open('../../figs/einstein.jpg').convert('L')
A = np.array(img)

U, s, Vt = np.linalg.svd(A)

Ak = U[:, :k] @ np.diag(s[:k]) @ Vt[:k, :]

error = np.linalg.norm(A - Ak, 'fro') #frobeinus this is

print(f"Rank {k} approximation Frobenius norm error: {error}")

k_values = np.arange(1, len(s) + 1)

plt.figure(figsize=(10, 5))
#plt.plot(k_values, s)
#plt.title('Singular Values')
#plt.xlabel('k')
#plt.ylabel('Magnitude')

plt.subplot(1, 2, 1)
plt.semilogy(k_values, s) # y is log, better range
plt.title('Singular Values v/s k')
plt.xlabel('k')
plt.ylabel('Magnitude')

energy = s**2

total_energy = np.sum(energy)

cumulative_energy = np.cumsum(energy)

cumulative_energy_percent = (cumulative_energy / total_energy) * 100

plt.subplot(1,2,2)
plt.plot(k_values, cumulative_energy_percent)
plt.title('Energy v/s k')
plt.xlabel('k')
plt.ylabel('Energy (%)')

plt.grid(True)

plt.axvline(x=50, color='g', linestyle=':', label='k=50') #makes x-int
plt.legend()

plt.savefig('../../figs/plot.png')
plt.show()
