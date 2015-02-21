 #!/usr/bin/env python3

 import numpy as np
 import sympy as sp
 import math
 import random

 import matplotlib.pyplot as plt

 plt.rc('text', usetex=True)
 plt.rc('font', family='serif')

 from matplotlib import cm
 from matplotlib.ticker import LinearLocator, FormatStrFormatter
 from mpl_toolkits.mplot3d import Axes3D

 NUM_ITER = 10
 MIN_T = 0
 MAX_T = 10
 NUM_T = 50

 a_b, D_b = sp.symbols("a_b D_b")
 ksi = b = sp.sympify("b")

 val_a_b = 0
 val_D_b = 3
 val_sigma_b = math.sqrt(val_D_b)

 A, w_1, t, phi = sp.symbols("A w_1 t phi")
 psi = sp.sympify("A * cos(w_1*t + phi)")

 val_a = math.pi/2
 val_A = 2
 val_w_1 = 1

 eta = ksi + psi.subs(
             {
                 A: val_A,
                 w_1: val_w_1
             }
         )
 # print("eta = ", sp.latex(eta))

 val_t = np.linspace(MIN_T, MAX_T, NUM_T)

 for _ in range(NUM_ITER):
     val_b = random.gauss(val_a_b, val_sigma_b)
     val_phi = random.uniform(-val_a, val_a)

     subs_eta = eta.subs(
         {
             A: val_A,
             w_1: val_w_1,
             b: val_b,
             phi: val_phi
         }
     )
     
     lambda_eta = sp.lambdify(t, subs_eta, "numpy")

     val_eta = np.vectorize(lambda_eta)(val_t)
     plt.plot(val_t, val_eta, color='g', linestyle='-',
              marker='.', markersize=5, mfc='g')

 a = sp.symbols("a")
 f_phi = sp.sympify("1 / (2 * a)")


 # E(psi) calculation
 E_psi = sp.integrate(psi * f_phi, (phi, -a, a))
 E = sp.simplify(a_b + E_psi)

 print("E = ", sp.latex(E))

 subs_E = E.subs(
             {
                 A: val_A,
                 w_1: val_w_1,
                 b: val_b,
                 a: val_a,
                 a_b: val_a_b
             })
     
 lambda_E = sp.lambdify(t, subs_E, "numpy")

 val_E = np.vectorize(lambda_E)(val_t)

 plot_E, = plt.plot(val_t, val_E, color='b', linestyle='-',
                    marker='.', markersize=5, mfc='b', label='$ E(\eta(t)) $')

 # D(psi) calculation
 psi_centered = sp.simplify(psi - E_psi)
 D_psi = sp.simplify(sp.integrate((psi_centered ** 2) * f_phi, (phi, -a, a)))
 D = sp.simplify(D_b + D_psi)

 print("D = ", sp.latex(D))

 subs_D = D.subs(
             {
                 A: val_A,
                 w_1: val_w_1,
                 b: val_b,
                 a: val_a,
                 D_b: val_D_b
             })

 lambda_D = sp.lambdify(t, subs_D, "numpy")

 val_D = np.vectorize(lambda_D)(val_t)
 plot_D, = plt.plot(val_t, val_D, color='r', linestyle='-',
                    marker='.', markersize=5, mfc='r', label='$ D(\eta(t)) $')

 plt.grid()
 plt.xlabel("$ t $")
 # plt.legend(handles=[plot_E, plot_D])
 # plt.savefig("values.png", dpi=100)

 # R(psi) calculation
 t_1, t_2 = sp.symbols("t_1 t_2")
 R_psi = sp.integrate(psi_centered.subs({t : t_1}) * psi_centered.subs({t : t_2}) * f_phi, (phi, -a, a))
 R = sp.simplify(D_b + R_psi)

 print("R = ", sp.latex(R))

 subs_R = R.subs(
             {
                 A: val_A,
                 w_1: val_w_1,
                 b: val_b,
                 a: val_a,
                 D_b: val_D_b
             })

 lambda_R = sp.lambdify((t_1, t_2), subs_R, "numpy")
 val_t_1, val_t_2 = np.meshgrid(val_t, val_t)
 val_R = np.vectorize(lambda_R)(val_t_1, val_t_2)

 fig_R = plt.figure(2)
 ax = fig_R.gca(projection="3d")
 surf_R = ax.plot_surface(val_t_1, val_t_2, val_R,
                          rstride=1, cstride=1, cmap=cm.coolwarm,
                          linewidth=0)
 ax.zaxis.set_major_locator(LinearLocator(10))
 ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

 fig_R.colorbar(surf_R, shrink=0.5, aspect=5)

 # plt.savefig("correlation.png", dpi=200)
 # plt.show()
