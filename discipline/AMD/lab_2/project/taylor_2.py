#!/usr/bin/env python

from copy import copy
import numpy as np
import sympy as sp

import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D
    
# performs substantiations for scalar syms_f: syms_x --> sym_a
def s_subs(sym_f, sym_x, sym_a):
    if len(sym_x) != len(sym_a):
        raise TypeError("subs2 arguments must have the same length")

    return sym_f.subs(zip(sym_x, sym_a))

# performs substantiations for matrix syms_m: syms_x --> sym_a
def m_subs(sym_m, sym_x, sym_a):
    if len(sym_x) != len(sym_a):
        raise TypeError("subs2 arguments must have the same length")

    res = copy(sym_m)
    for cur_sym_x, cur_sym_a in zip(sym_x, sym_a):
        res = res.subs(cur_sym_x, cur_sym_a)
    return res

# computes f(X)
def val2(sym_f, sym_x, val_x):
    if len(sym_x) != len(val_x):
        raise TypeError("val2 arguments must have the same length")

    res = sym_f.subs(zip(sym_x, val_x))
    return float(res)

# returns python's f(val_x)
def lambdify2(sym_f, sym_x):
    return sp.lambdify(sym_x, sym_f)

# computes partial difference of sym_f
# by each of sym_x[i]
# return scalar value
def s_diff(sym_f, sym_x):
    res = []
    for cur_sym_x in sym_x:
        res.append(sym_f.diff(cur_sym_x))

    return res

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

# computes X - Y' in vector form
# return vector value
def v_minus(X, Y):
    if len(X) != len(Y):
        raise TypeError("v_minus arguments must have the same length")

    res = []
    for i,_ in enumerate(X):
        res.append(X[i] - Y[i])

    return res
    
# returns symbolic Taylor approximation of function
def taylor2(sym_f, sym_x, sym_a):
    if len(sym_x) != len(sym_a):
        raise TypeError("taylor2 arguments must have the same length")

    m_sym_x = sp.Matrix(sym_x)
    m_sym_a = sp.Matrix(sym_a)
    
    sym_dst = m_sym_x - m_sym_a
    print("sym_dst:", sym_dst)
    
    A = m_subs(sp.Matrix(s_diff(sym_f, sym_x)), sym_x, sym_a)
    print("A:", A)

    B = m_subs(sp.hessian(sym_f, sym_x), sym_x, sym_a)
    print("B:", B)
    
    sym_appr = s_subs(sym_f, sym_x, sym_a)
    sym_appr += (A.T * sym_dst)[0,0]
    sym_appr += sp.sympify('0.5') * (sym_dst.T * B * sym_dst)[0,0]
    
    return sp.simplify(sym_appr)


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
plot2(real_f, VALS_X, VALS_Y, 'real_2.png')

sym_appr_f = taylor2(SYM_REAL_F, SYM_X, SYM_A)

appr_f = sp.lambdify(
    SYM_X,
    s_subs(sym_appr_f, SYM_A, VAL_A)
)

print('Taylor\'s approximation: {}'.format(
    sym_appr_f
))
    
plot2(appr_f, VALS_X, VALS_Y, 'taylor_2.png')
