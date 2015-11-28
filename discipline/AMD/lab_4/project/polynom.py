#!/usr/bin/env python

import functools
import numpy as np
import tools.multidim as multidim

import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D


def permutations(n, s):
    '''
    Generates all possible lists with length n and sum s
    '''
    if n == 1:
        yield (s,)
    else:
        for i in range(s+1):
            for j in permutations(n-1, s-i):
                yield(i,) + j

def mult2(x, power):
    '''
    Computes (x[1] ** power[1]) *
             (x[2] ** power[2]) *
                     ...
             (x[-1] ** power[-1])
    '''
    if len(x) != len(power):
        raise TypeError("mult2 arguments must have the same length")

    res = 1
    for idx,_ in enumerate(x):
        res *= x[idx] ** power[idx]

    return res


def polyval_classic(c, x):
    '''
    Computes value of polynom using classic approach

    Arguments:
      c -- array of coefficients,
      x -- array of variable values.

    Return:
      polynom value as scalar value.
    '''
    power = len(c)
    num_x = len(x)
    res = 0

    for cur_power in range(power):
        for cur_perm in permutations(num_x, cur_power):
            cur_c = c[cur_power][cur_perm[0]]
            cur_x = mult2(x, cur_perm)
            res += cur_c * cur_x

    return res

def plot2(f, coeffs, val_x, val_y, filename):
    '''
    Plots 3D representation of function
    '''
    mesh_val_x, mesh_val_y = np.meshgrid(val_x, val_y)
    shape = mesh_val_x.shape
    mesh_r = np.zeros(shape)

    for row_idx in range(shape[0]):
        for col_idx in range(shape[1]):
            cur_x = mesh_val_x[row_idx][col_idx]
            cur_y = mesh_val_y[row_idx][col_idx]
            mesh_r[row_idx][col_idx] = float(f(coeffs, np.array([cur_x, cur_y])))

    figure = plt.figure()
    ax = figure.gca(projection='3d')
    surface = ax.plot_surface(mesh_val_x, mesh_val_y, mesh_r,
                              rstride=1, cstride=1, cmap=cm.coolwarm,
                              linewidth=0)

    ax.zaxis.set_major_locator(LinearLocator(10))
    ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

    plt.savefig(filename, dpi=200)
    figure.clear()

if __name__ == '__main__':
    MIN_X1, MIN_X2 = -0.5, -0.5
    MAX_X1, MAX_X2 = 0.5, 0.5
    NUM_X1, NUM_X2 = 10, 10

    VALS_X1 = np.linspace(MIN_X1, MAX_X1, NUM_X1)
    VALS_X2 = np.linspace(MIN_X2, MAX_X2, NUM_X2)

    classic_c = np.array(
        [[1],
         [1, 1],
         [2, 2, 2],
         [3, 3, 3, 3],
         [12, 12, 12, 12, 12]])

    plot2(polyval_classic, classic_c, VALS_X1, VALS_X2, 'polynom_classic.png')
    # print(polyval_classic(classic_c, np.array([0.7, 1.7])))

    c0 = np.array([1])
    c1 = np.array([1, 1])
    c2 = np.array([[2, 1],
                   [1, 2]])
    c3 = np.array([[[3, 1],
                    [1, 1]],
                   [[1, 1],
                    [1, 3]]])
    c4 = np.array([[[[12, 3],
                     [3, 2]],
                    [[3, 2],
                     [2, 3]]],
                   [[[3, 2],
                    [2, 3]],
                    [[2, 3],
                    [3, 12]]]])

    multidim_c = [c0, c1, c2, c3, c4]

    plot2(multidim.polyval, multidim_c, VALS_X1, VALS_X2, 'polynom_multidim.png')
    # print(multidim.polyval(multidim_c, np.array([0.7, 1.7])))
