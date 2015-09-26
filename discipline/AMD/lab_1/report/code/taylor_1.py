 import numpy as np
 import sympy as sp
 import matplotlib.pyplot as plt

 plt.rc('text', usetex=True)
 plt.rc('font', family='serif', size=20)

 sym_x = sp.symbols('x')
 sym_f = sp.sympify('x**6 - 2*x - 7')

 f = sp.lambdify(sym_x, sym_f)

 appr_point = 1

 x = np.linspace(0.5, 1.5, 10)
 y = np.vectorize(f)(x)

 colors = ['r', 'g', 'b']
 num_colors = len(colors)

 markers = ['x','.','o','v','d']
 num_markers = len(markers)

 plt.plot(x, y,
          color='r', linestyle='-',
          marker='x', markersize=10,
          mfc='r', label='$ y(x) $')

 for appr_precision in range(1, 5):
     cfs = sp.mpmath.taylor(f, appr_point, appr_precision)[::-1]
     appr_f = lambda x: sp.mpmath.polyval(cfs, x)
     appr_y = np.vectorize(appr_f)(x - appr_point)
     
     plt.plot(x, appr_y,
              color=colors[appr_precision % num_colors],
              linestyle='-',
              marker=markers[appr_precision % num_markers],
              markersize=5,
              label='$ f_{}(x) $'.format(appr_precision))

 plt.xlabel('$ X $')
 plt.ylabel('$ Y $')        
 plt.grid(True)    
 plt.legend(loc=2)    
 plt.savefig('taylor_1.png', dpi=200)
