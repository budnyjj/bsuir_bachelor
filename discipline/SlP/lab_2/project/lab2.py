#!/usr/bin/env python3

import random

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

def gen_values(values, event_probs, n):
    for event in gen_events(event_probs, n):
        yield values[event]

p=[0, 0.3, 0.7]
x=[-1, 0, 1]
n = 10

events = []
values = []

for event in gen_events(p, n):
    events.append(event)

print("Task #1")
print("=======")    
print("Events: ", events)
print("Avg events:", avg(events))
print("Disp events:", disp(events))
    
for value in gen_values(x, p, n):
    values.append(value)

print()
print("Task #2")
print("=======")   
print("Values: ", values)
print("Avg values:", avg(values))
print("Disp values:", disp(values))
