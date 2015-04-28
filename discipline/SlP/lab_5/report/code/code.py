 #!/usr/bin/env python3

 import numpy as np
 import matplotlib.pyplot as plt

 plt.rc('text', usetex=True)
 plt.rc('font', family='serif')


 def limit_state_probs(p):
     a = np.matrix(p)
     for i,_ in enumerate(p):
         a[i,i] -= 1

     a = np.concatenate(
         (
             a.T[:-1],
             np.ones((1, len(p[0]))
             )
         ),
     )

     b = np.zeros((len(p[0])-1, 1))
     b = np.concatenate(
         (
             b,
             np.array([[1]])
         )
     )

     res = a.I * b
     return res.flatten()


 p = np.array(
     [
         [0.6, 0,   0.4],
         [0.4, 0.6, 0],
         [0.4, 0.2, 0.4]
     ]
 )

 print("LIMIT STATE PROBABILITIES:", limit_state_probs(p))