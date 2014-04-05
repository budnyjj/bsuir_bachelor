import math
import matplotlib.pyplot as plt
from matplotlib import rc

rc('font',**{'family':'serif','serif':['Palatino']})
rc('text', usetex=True)

def fill_data(src_fname):
    dest_data = []
    with open(src_fname) as f:
        for line in f:
            raw_data = line.split()
            dest_data.append([float(data) for data in raw_data[1:]])
    return dest_data

def print_data(src_data):
    for i, variant in enumerate(src_data):
        print("{}: ".format(i), end="")
        print(variant)

def transpose(src_data):
    return [list(row) for row in zip(*src_data)]

def maximals(src_data):
    return [max(param) for param in src_data]

def normalize(data):
    t_data = transpose(data)
    max_vals = maximals(t_data)
    for i, variant in enumerate(t_data):
        t_data[i] = [param/max_vals[i] for param in variant]
    return transpose(t_data)

def average(cluster, data):
    t_data = transpose(data)
    avg = [0 for param in t_data]
    for i, param in enumerate(t_data):
        for j in cluster:
            avg[i] += t_data[i][j]
        avg[i] /= len(cluster)
    return avg

def distance(variant, master):
    dst = 0
    for i, param in enumerate(variant):
        dst += (param - master[i]) ** 2
    return math.sqrt(dst)

def plot(fname, clusters, data):
    colors = ["r", "g", "b", "c", "m", "y", "k"]
    for c, cluster in enumerate(clusters):
        for i in cluster:
            plt.plot(data[i][0], data[i][1], colors[c] + "o")
    plt.savefig(fname)

def equals(cluster_a, cluster_b):
    for i, val in enumerate(cluster_a):
        try:
            if val != cluster_b[i]:
                return False
        except IndexError:
            return False
    return True
