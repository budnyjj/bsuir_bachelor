#!/usr/bin/env python

import itertools
import numpy as np

def flatten(*iters):
    '''
    Return flatten list.

    Example: [[a], [b]] -> [a, b]
    '''
    res = []
    for it in iters:
        res.extend(it)

    return tuple(res)

def mult_iter(iterable):
    res = 1
    for val in iterable:
        res *= val
    return res

def multi_idxs(shape):
    '''
    Generate all possible multiindex values with specified shape.

    Example: (1,2) -> (0,0), (0,1)
    '''
    multi_idx_values = []
    for dim_sz in shape:
        multi_idx_values.append([idx for idx in range(dim_sz)])

    return itertools.product(*multi_idx_values)

def dot(a, b, lmd, mu):
    '''
    Return (lmd,mu)-dot product of multidimensional matrices.
    '''
    shape_a = a.shape
    shape_b = b.shape

    print("shape_a: ", shape_a)
    print("shape_b: ", shape_b)

    num_dims_a = len(shape_a)
    num_dims_b = len(shape_b)

    if num_dims_a - lmd - mu < 0:
        raise TypeError("Number of dimensions in matrix A "\
                        "should be not less than lambda + mu")

    if num_dims_b - lmd - mu < 0:
        raise TypeError("Number of dimensions in matrix B"\
                        "should be not less than lambda + mu")

    for dim_idx in range(lmd + mu):
        if shape_b[dim_idx] != shape_a[num_dims_a-dim_idx-1]:
            raise TypeError("Sizes of dimensions in matrices"\
                            "A and B should be conformed")

    print("idx_l: {}:{}".format(0, num_dims_a-lmd-mu))
    print("idx_s: {}:{}".format(num_dims_a-lmd-mu, num_dims_a-mu))
    print("idx_c: {}:{}".format(num_dims_a-mu, num_dims_a))
    print("idx_m: {}:{}".format(lmd+mu, num_dims_b))

    shape_l = shape_a[:num_dims_a-lmd-mu]
    shape_s = shape_a[num_dims_a-lmd-mu:num_dims_a-mu]
    shape_c = shape_a[num_dims_a-mu:]
    shape_m = shape_b[lmd+mu:]

    print("shape_l: ", shape_l)
    print("shape_s: ", shape_s)
    print("shape_c: ", shape_c)
    print("shape_m: ", shape_m)

    res = np.zeros(flatten(shape_l, shape_s, shape_m))
    print("shape_res: ", res.shape)

    for multi_idx_l in multi_idxs(shape_l):
        for multi_idx_s in multi_idxs(shape_s):
            for multi_idx_m in multi_idxs(shape_m):
                multi_idx_res = flatten(multi_idx_l,multi_idx_s,multi_idx_m)
                for multi_idx_c in multi_idxs(shape_c):
                    multi_idx_a = flatten(multi_idx_l,multi_idx_s,multi_idx_c)
                    multi_idx_b = flatten(multi_idx_c,multi_idx_s,multi_idx_m)

                    print("res[{}] += a[{}] * b[{}] = {} * {} = {}".format(
                        multi_idx_res, multi_idx_a, multi_idx_b,
                        a[multi_idx_a], b[multi_idx_b], a[multi_idx_a] * b[multi_idx_b]
                    ))

                    res[multi_idx_res] += a[multi_idx_a] * b[multi_idx_b]

    return res

def ones(lmd, mu, n):
    '''
    Return E(lmd, mu) with dim size n: A * E = E * A = A
    '''
    l_shape = tuple([n for _ in range(mu)])
    s_shape = tuple([n for _ in range(lmd)])
    c_shape = l_shape

    res_shape = flatten(l_shape, s_shape, c_shape)
    res = np.zeros(res_shape)

    for multi_idx_l in multi_idxs(l_shape):
        for multi_idx_c in multi_idxs(c_shape):
            if multi_idx_l == multi_idx_c:
                for multi_idx_s in multi_idxs(s_shape):
                    multi_idx_res = flatten(multi_idx_l,multi_idx_s,multi_idx_c)
                    res[multi_idx_res] = 1

    return res

if __name__ == "__main__":
    N = 4
    P, Q = 4, 4
    T = (1, 2, 3, 0)
    LMD, MU = 0, 3

    # N = 2
    # P, Q = 3, 3
    # LMD, MU = 2, 1

    shape_a = tuple([N for _ in range(P)])
    shape_b = tuple([N for _ in range(Q)])

    a = np.arange(mult_iter(shape_a)).reshape(shape_a)
    b = np.arange(mult_iter(shape_b)).reshape(shape_b)

    print("a:\n", a)
    print("b:\n", b)

    print("a.T:\n", np.transpose(a, T))

    print("({},{})^(a b):\n{}".format(LMD, MU, dot(a, b, LMD, MU)))
    print("E({}, {}):\n{}".format(LMD, MU, ones(LMD, MU, N)))

    print("({0},{1})^(E({0},{1}) a):\n{2}".format(LMD, MU, dot(ones(LMD, MU, N), a, LMD, MU)))
