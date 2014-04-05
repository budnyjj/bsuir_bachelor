import copy

import data as dt

def suitable_cluster(variant, masters):
    distances = [dt.distance(variant, master) for master in masters]
    val, idx = min((val, idx) for (idx, val) in enumerate(distances))
    return idx

def k_averages(data, init_clusters):
    prev_clusters = [[] for i in init_clusters]
    clusters = copy.deepcopy(prev_clusters)

    masters = [data[i] for i in init_clusters]

    for i, variant in enumerate(data):
        clusters[suitable_cluster(variant, masters)].append(i)

    while not dt.equals(clusters, prev_clusters):
        prev_clusters = copy.deepcopy(clusters)

        for i, cluster in enumerate(clusters):
            masters[i] = dt.average(cluster, data)

        clusters = [[] for i in init_clusters]
        for i, variant in enumerate(data):
            clusters[suitable_cluster(variant, masters)].append(i)

    return clusters




def new_candidate(master, candidates, data):
    distances = [(dt.distance(data[i], master), i) for i in candidates]
    val, idx = max(distances)
    return idx, val

def avg_distance(masters):
    dst = 0
    masters_len = len(masters)
    for m1 in masters:
        for m2 in masters:
            if m1 != m2:
                dst += dt.distance(m1, m2)
    return dst / (masters_len * (masters_len - 1))

def max_min(data):
    masters = [data[0], ]
    init_clusters = [[], ] # one cluster

    candidate, dst = new_candidate(masters[0], range(len(data)), data)
    masters.append(data[candidate])
    init_clusters.append([])

    threshold = dst / 2

    clusters = copy.deepcopy(init_clusters)
    for i, variant in enumerate(data):
        clusters[suitable_cluster(variant, masters)].append(i)

    less_than_threshold = False

    while not less_than_threshold:
        less_than_threshold = True
        for c, cluster in enumerate(clusters):
            candidate, dst = new_candidate(masters[c], cluster, data) 
            if dst >= threshold: # add new cluster
                less_than_threshold = False
                masters.append(data[candidate])
                candidate_idx = clusters[c].index(candidate) 
                del clusters[c][candidate_idx]
                init_clusters.append([])
    
        clusters = copy.deepcopy(init_clusters)
        for i, variant in enumerate(data):
            clusters[suitable_cluster(variant, masters)].append(i)
        
        threshold = avg_distance(masters) / 2
    
    return clusters



