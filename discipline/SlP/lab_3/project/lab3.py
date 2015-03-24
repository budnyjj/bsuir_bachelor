#!/usr/bin/env python3

import random
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

def avg(lst):
    return sum(lst) / float(len(lst))

def disp(lst):
    res = 0
    a = avg(lst)
    for v in lst:
        res += (v - a) ** 2
    return res / float(len(lst))

def event_idx(sum_event_probs, val):
    for i, prob in enumerate(sum_event_probs):
        if val < prob:
            return i

def gen_events(event_probs, n):
    sum_ps = event_probs[:]
    
    for i in range(1, len(sum_ps)):
        sum_ps[i] = sum_ps[i-1] + sum_ps[i]

    if sum_ps[-1] != 1:
        raise ValueError("Sum of event probabilities != 1")

    for _ in range(n):
        v = random.uniform(0, 1)
        yield event_idx(sum_ps, v)

def gen_event(event_probs):
    for event in gen_events(event_probs, 1):
        return event

def gen_chain(values, hop_probs, start_event_probs, chain_length):
    start_event = gen_event(start_event_probs)
    chain_events = [start_event]
    
    for i in range(1, chain_length):
        cur_event = gen_event(hop_probs[chain_events[i-1]])
        chain_events.append(cur_event)
    return chain_events
        
def events_to_values(events, values):
    res = []
    for event in events:
        res.append(values[event])
    return res

def gen_values(values, event_probs, n):
    for event in gen_events(event_probs, n):
        yield values[event]


a=[0.3, 0.7, 0]
p = [[0.6, 0,   0.4],
     [0.4, 0.6, 0],
     [0.4, 0.2, 0.4]]
x=[5, 6, 7]
n = 30

idx_chain = [i for i in range(1, n+1)]
events_chain = gen_chain(x, p, a, n)
values_chain = events_to_values(events_chain, x)

print("Events chain:", events_chain)
print("Values chain:", values_chain)

plt.plot(idx_chain, values_chain, color='g', linestyle='steps',
         marker='.', markersize=5, mfc='g')
plt.axis([1, n, min(x)-1, max(x)+1])
plt.grid(True)

plt.savefig("chain.png", dpi=200)
plt.show()
