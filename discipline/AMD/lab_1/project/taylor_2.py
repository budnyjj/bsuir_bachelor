#!/usr/bin/env python

from copy import copy
import sympy as sp

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
    # TODO: check, if len(sym_f) == len(vals)    
    res = sp.sympify('1')
    for idx,_ in enumerate(sym_f):
        res *= sym_f[idx] ** sp.sympify(vals[idx])
        
    return res

# computes partial difference of sym_f
# by each of sym_x[i] times[i] times
def diff2(sym_f, sym_x, times):
    # TODO: Check, if len(sym_x) == len(times)
    res = copy(sym_f)
    
    for idx,cur_sym_x in enumerate(sym_x):
        for _ in range(times[idx]):
            res = sp.diff(res, cur_sym_x)
    
    return res

# performs substantiations for syms_f: syms_x --> sym_a
def subs2(sym_f, sym_x, sym_a):
    # TODO: Check, if len(sym_x) == len(sym_a)
    return sym_f.subs(zip(sym_x, sym_a))

# computes f(X)
def val2(sym_f, syms_x, vals):
    # TODO: Check, if len(sym_x) == len(x)
    res = sym_f.subs(zip(sym_x, val_x))
    return float(res)

# returns symbolic Taylor approximation of function
def taylor2(sym_f, sym_x, sym_a, appr_precision=0):
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

appr_precision = 3
sym_f = sp.sympify('(x_1 + x_2)**6 - 2*(x_1 + x_2) - 7')
sym_x = sp.symbols('x_1 x_2')
sym_a = sp.symbols('a_1 a_2')

val_a = (1, 1)
val_x = (0.9, 0.9)

# print(mult2(sym_x, [1,2]))
# print(subs2(sym_f, sym_x, sym_a))
sym_appr_f = taylor2(sym_f, sym_x, sym_a, appr_precision)
appr_f = subs2(sym_appr_f, sym_a, val_a)

print("Function:", sym_f)
print("Appr function:", sym_appr_f)
print("Value:", val2(sym_f, sym_x, val_x))
print("Appr value:", val2(appr_f, sym_x, val_x))
