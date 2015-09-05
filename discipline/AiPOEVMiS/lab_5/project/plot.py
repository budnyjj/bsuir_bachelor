import matplotlib.pyplot as plt
import temperature as tmp

c = [x / 0.8 for x in range(-100, 100, 5)]
f = map(tmp.c2f, c)

plt.xlabel("Celsius")
plt.ylabel("Fahrenheight")
plt.grid(True)
plt.plot(c, f,
         color="b", linestyle="--",
         marker=".", markersize=10, mfc="r")
plt.show()
