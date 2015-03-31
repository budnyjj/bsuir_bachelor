#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

def gen_hop_probs(p, n=2):
    cur_hop_probs = p.copy()
    for _ in range(n+1):
        yield cur_hop_probs
        cur_hop_probs = np.dot(cur_hop_probs, p)

def avg_state(state_prob, values):
    res = 0
    for i,v in enumerate(values):
        res += v * state_prob[i]
    return res
        
p = np.array(
    [
        [0.6, 0,   0.4],
        [0.4, 0.6, 0],
        [0.4, 0.2, 0.4]
    ]
)

a = np.array([0.3, 0.7, 0])

e = np.array([5, 6, 7])

NUM_STEPS = 10

hop_probs = np.empty(shape=(3,1))
state_probs = np.empty(shape=(3,1))
avg_state_probs = []

for i,hop_prob in enumerate(gen_hop_probs(p, NUM_STEPS)):
    print("PROBABILITY MATRIX #{}:\n{}".format(i, hop_prob))
    if i == 0:
        hop_probs = np.vstack(hop_prob[0])
    else:
        hop_probs = np.concatenate(
            (
                hop_probs,
                np.vstack(hop_prob[0])
            ), axis = 1
        )
    # print(hop_probs)
    state_prob = np.dot(a, hop_prob)
    print("STATE PROBABILITIES #{}:\n{}".format(i, state_prob))
    
    if i == 0:
        state_probs = np.vstack(state_prob)
    else:
        state_probs = np.concatenate(
            (
                state_probs,
                np.vstack(hop_prob[0])
            ), axis = 1
        )
    # print(state_probs)

    avg_state_prob = avg_state(state_prob, e)
    print("AVERAGE STATE:", avg_state_prob)
    
    avg_state_probs.append(avg_state_prob)    
    print()

idxs = [i for i in range(0, NUM_STEPS+1)]

plt.figure(0)
plt.title("First row of inter-state hop probabilities")
plt.grid(True)
for state in hop_probs:
    plt.plot(idxs, state, marker='.', markersize=5)
plt.savefig("hop_probs.png", dpi=120)
    
plt.figure(1)
plt.title("Limit state probabilities")
plt.grid(True)
for state in state_probs:
    plt.plot(idxs, state, marker='.', markersize=5)
plt.savefig("state_probs.png", dpi=120)
    
plt.figure(2)
plt.title("Average state")
plt.grid(True)
plt.plot(idxs, avg_state_probs, marker='.', markersize=5)
plt.savefig("avg_state.png", dpi=120)

#plt.show()
