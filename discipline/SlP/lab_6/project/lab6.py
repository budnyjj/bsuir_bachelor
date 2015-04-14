#!/usr/bin/env python3

import math
import random

import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

def event_idx(sum_event_probs, val):
    for i, prob in enumerate(sum_event_probs):
        if val < prob:
            return i

def _gen_event(event_probs, eps_prob=0.00001):
    sum_ps = event_probs[:]
    
    for i in range(1, len(sum_ps)):
        sum_ps[i] = sum_ps[i-1] + sum_ps[i]

    if (abs(sum_ps[-1]-1) > eps_prob):
        raise ValueError(
            "Sum of event probabilities ({}) != 1".format(
                sum_ps[-1])
        )

    v = random.uniform(0, 1)
    return event_idx(sum_ps, v)

def _puasson_probs(t, lambd, eps_prob=0.00001):
    probs = []
    delta_prob = 1
    k = 0
    k_fact = 1 # == k!

    while delta_prob > eps_prob:
        cur_prob = (lambd * t) ** k
        cur_prob /= k_fact
        cur_prob *= math.exp(-lambd * t)

        probs.append(cur_prob)
        delta_prob -= cur_prob
        
        k += 1
        k_fact *= k

    probs.append(delta_prob)
    
    return probs



def puasson_1(a, b, lambd):
    t = [a]
    sum_t = a

    while sum_t <= b:
        dt = random.expovariate(lambd)
        t.append(dt)
        sum_t += dt

    for i in range(1, len(t)):
        t[i] += t[i-1]   

    if t[-1] > b:
        del t[-1]
        
    return t

def puasson_2(a, b, lambd):
    t = []

    probs = _puasson_probs(b-a, lambd)
    n = _gen_event(probs)

    for _ in range(n):
        t.append(random.uniform(a, b))

    return sorted(t)

def to_delta(values):
    delta_values = []
    for i in range(1,len(values)):
        delta_values.append(values[i] - values[i-1])

    return delta_values

NUM_BINS = 10

a = 0
b = 50
lambd = 6

puasson_values_1 = puasson_1(a, b, lambd)
puasson_values_2 = puasson_2(a, b, lambd)

delta_puasson_values_1 = to_delta(puasson_values_1)
delta_puasson_values_2 = to_delta(puasson_values_2)

plt.figure(0)
plt.grid(True)
plt.axis([a, b, 0.5, 2.5])
plt.xlabel('$ t $')
plt.plot(puasson_values_1, [1 for _ in puasson_values_1],
         marker='.', linestyle=' ', markersize=5)
plt.plot(puasson_values_2, [2 for _ in puasson_values_2],
         marker='.', linestyle=' ', markersize=5)
plt.savefig("times.png", dpi=200)

plt.figure(1)
plt.grid(True)
plt.xlabel('$ \\Delta t $')
plt.ylabel('$ p $')
plt.hist(delta_puasson_values_1, NUM_BINS, normed=True)
plt.axis([0, max(delta_puasson_values_1), 0, 6])
plt.savefig("hist_1.png", dpi=200)

plt.figure(2)
plt.grid(True)
plt.xlabel('$ \\Delta t $')
plt.ylabel('$ p $')
plt.hist(delta_puasson_values_2, NUM_BINS, normed=True)
plt.axis([0, max(delta_puasson_values_2), 0, 6])
plt.savefig("hist_2.png", dpi=200)

plt.show()
