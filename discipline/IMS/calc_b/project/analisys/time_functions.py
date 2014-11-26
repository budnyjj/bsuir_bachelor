import matplotlib.pyplot as plt

def time_max(zps):
    return (-20*zps + 400) / 17.0

def time_min(zps):
    return (-10*zps + 200) / 17.0

zapas = [0, 3, 20]
t_min = map(time_min, zapas)
t_max = map(time_max, zapas)

plt.xlabel("ZAPAS")
plt.ylabel("TIME")
plt.grid(True)
plt.plot(zapas, t_min,
         zapas, t_max,
         color="b", linestyle="--",
         marker=".", markersize=10, mfc="r")
plt.show()
