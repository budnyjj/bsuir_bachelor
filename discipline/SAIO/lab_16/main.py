#!/usr/bin/python

import data as dt
import clusters as cl
    
data = dt.fill_data("in/src_data.txt")

print("=== INIT DATA ===")
dt.print_data(data)

data = dt.normalize(data)

print("=== NORMALIZED DATA ===")
dt.print_data(data)

k_clusters = cl.k_averages(data, [4,2,8])
print("=== K AVERAGE ===")
print(k_clusters)

dt.plot("out/k_average.png", k_clusters, data)

mm_clusters = cl.max_min(data)
print("=== MAXIMIN ===")
print(mm_clusters)

dt.plot("out/maximin.png", mm_clusters, data)
