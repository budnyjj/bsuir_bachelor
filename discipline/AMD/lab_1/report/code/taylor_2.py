 from copy import copy
 import numpy as np
 import sympy as sp
 import matplotlib.pyplot as plt
 plt.rc('text', usetex=True)
 plt.rc('font', family='serif')
 from matplotlib import cm
 from matplotlib.ticker import LinearLocator, FormatStrFormatter
 from mpl_toolkits.mplot3d import Axes3D

 # Generates all possible lists with length n and sum s
 def permutations(n, s):
     if n == 1:
         yield (s,)
     else:
         for i in range(s+1):
             for j in permutations(n-1, s-i):
                 yield(i,) + j

 # computes factorial                
 def fact(val):
     res = 1
     for i in range(1,val+1):
         res *= i
     return res
                 
 # computes vals[0]! * vals[1]! * ... * vals[-1]!
 def fact2(vals):
     res = 1
     for val in vals:
         res *= fact(val)
     return res

 # computes
 # (sym_f[1] ** vals[1]) *
 # (sym_f[2] ** vals[2]) *
 # ...
 # (sym_f[-1] ** vals[-1])
 def mult2(sym_f, vals):
     if len(sym_f) != len(vals):
         raise TypeError("mult2 arguments must have the same length")

     res = sp.sympify('1')
     for idx,_ in enumerate(sym_f):
         res *= sym_f[idx] ** sp.sympify(vals[idx])
         
     return res

 # computes partial difference of sym_f
 # by each of sym_x[i] times[i] times
 def diff2(sym_f, sym_x, times):
     if len(sym_x) != len(times):
         raise TypeError("diff2 arguments must have the same length")

     res = copy(sym_f)
     
     for idx,cur_sym_x in enumerate(sym_x):
         for _ in range(times[idx]):
             res = sp.diff(res, cur_sym_x)
     
     return res

 # performs substantiations for syms_f: syms_x --> sym_a
 def subs2(sym_f, sym_x, sym_a):
     if len(sym_x) != len(sym_a):
         raise TypeError("subs2 arguments must have the same length")

     return sym_f.subs(zip(sym_x, sym_a))

 # computes f(X)
 def val2(sym_f, sym_x, val_x):
     if len(sym_x) != len(val_x):
         raise TypeError("val2 arguments must have the same length")

     res = sym_f.subs(zip(sym_x, val_x))
     return float(res)

 # returns python's f(val_x)
 def lambdify2(sym_f, sym_x):
     return sp.lambdify(sym_x, sym_f)

 # plots 3D representation of function
 def plot2(f, val_x, val_y, filename):
     mesh_val_x, mesh_val_y = np.meshgrid(val_x, val_y)
     mesh_r = np.vectorize(f)(mesh_val_x, mesh_val_y)

     figure = plt.figure()
     ax = figure.gca(projection='3d')
     surface = ax.plot_surface(mesh_val_x, mesh_val_y, mesh_r,
                               rstride=1, cstride=1, cmap=cm.coolwarm,
                               linewidth=0)

     ax.zaxis.set_major_locator(LinearLocator(10))
     ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
     
     plt.savefig(filename, dpi=200)
     figure.clear()

 # returns symbolic Taylor approximation of function
 def taylor2(sym_f, sym_x, sym_a, appr_precision=0):
     if len(sym_x) != len(sym_a):
         raise TypeError("taylor2 arguments must have the same length")

     num_x = len(sym_x)
     num_a = len(sym_a)

     # compute symbolic distance: (x_i - a_i)
     sym_dst = []
     for cur_sym_x,cur_sym_a in zip(sym_x, sym_a):
         sym_dst.append(cur_sym_x - cur_sym_a)
     
     # TODO: check, that num_x == num_a
     sym_appr = sp.sympify('0')
     
     for k in range(appr_precision+1):
         for diff_idxs in list(permutations(num_x,k)):
             sym_part_1 = sp.sympify(
                 '1/{}'.format(
                     fact2(diff_idxs)
                 )
             )

             sym_part_2 = diff2(
                 sym_f,
                 sym_x,
                 diff_idxs
             )
             
             sym_part_2 = subs2(sym_part_2, sym_x, sym_a)
             
             sym_part_3 = mult2(
                 sym_dst,
                 diff_idxs
             )
             
             sym_appr += sym_part_1 * sym_part_2 * sym_part_3

     return sym_appr

 # Maximal power of members in Taylor's approximation,
 # 0 -- no approximation
 MAX_APPR_PRECISION = 4
 SYM_REAL_F = sp.sympify('(x_1 + x_2)**6 - 2*(x_1 + x_2) - 7')

 SYM_X = sp.symbols('x_1 x_2')
 SYM_A = sp.symbols('a_1 a_2')
 VAL_A = (1, 1)

 MIN_X = 0.5
 MAX_X = 1.5
 NUM_X = 10
 MIN_Y = 0.5
 MAX_Y = 1.5
 NUM_Y = 10

 VALS_X = np.linspace(MIN_X, MAX_X, NUM_X)
 VALS_Y = np.linspace(MIN_Y, MAX_Y, NUM_Y)
 real_f = sp.lambdify(SYM_X, SYM_REAL_F)

 print('Source function:', SYM_REAL_F)
 plot2(real_f, VALS_X, VALS_Y,
       'real_2.png')

 for cur_appr_precision in range(MAX_APPR_PRECISION + 1):
     sym_appr_f = taylor2(SYM_REAL_F, SYM_X, SYM_A,
                          cur_appr_precision)
     appr_f = sp.lambdify(
         SYM_X,
         subs2(sym_appr_f, SYM_A, VAL_A)
     )

     print('Taylor\'s approximation #{}: {}'.format(
         cur_appr_precision,
         sym_appr_f
     ))
     
     plot2(appr_f, VALS_X, VALS_Y,
           'taylor_2_{}.png'.format(cur_appr_precision))
