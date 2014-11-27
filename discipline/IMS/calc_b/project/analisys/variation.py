import matplotlib.pyplot as plt

min_vals = range(0,20)

num_parts = [
    154,
    153,
    153,
    153,
    156,
    154,
    156,
    155,
    153,
    153,
    153,
    153,
    149,
    154,
    153,
    157,
    153,
    155,
    152,
    156
]

plt.xlabel("ZAPAS")
plt.ylabel("FINISH")
plt.grid(True)
plt.plot(min_vals, num_parts,
         color="b", linestyle="--",
         marker=".", markersize=10, mfc="r")
plt.show()
