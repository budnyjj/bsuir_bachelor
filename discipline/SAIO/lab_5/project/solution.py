#!/bin/python2

import math 
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

rc('font',**{'family':'serif','serif':['Palatino']})
rc('text', usetex=True)


def min_deposit(x, step_no):
    return (0.3**step_no)*x

def max_deposit(x, step_no):
    return (0.75**step_no)*x

def my_range(begin, end, step): # generates [begin:end+step:step]
    res=[]
    cur_val=begin
    while cur_val<=end:
        res.append(cur_val)
        cur_val+=step
    res.append(cur_val)
    return res

def my_index(lst, val, **kwargs): # get row index with specified 'z' float value
    EPS=kwargs.setdefault('eps', 0.03)
    for i, row in enumerate(lst):
        # print row['z']
        if (math.fabs(row['z']-val) < EPS):
            return i

def f(x, z, f_optimized=None):
    res=2-(math.exp(-x)+math.exp(-2*(z-x)))
    if f_optimized:
        res+=f_optimized(0.75*x + 0.3*(z-x)) 
    return res

def generate(z, f, f_optimized=None): # generate plot data for current step
    res={'data': [], 'max': {'x': [], 'f': []}}
    for i, cur_z in enumerate(z):
        data={'z': cur_z}
        data['x']=z[:i+1]
        data['f']=[f(x, cur_z, f_optimized) for x in data['x']]
        res['data'].append(data)

        max_f = -1;
        max_x = -1;
        for j, cur_f in enumerate(data['f']):
            if cur_f > max_f:
                max_f = cur_f
                max_x = data['x'][j]
        
        res['max']['x'].append(max_x)     
        res['max']['f'].append(max_f)
        
    return res

def polyfit(x, y, num_points): # polyfit with uniform points distribution
    density = len(x)/num_points
    args_x = x[::density]
    args_y = y[::density]
    if args_x[-1] != x[-1]:
        args_x.append(x[-1])
        args_y.append(y[-1])
    return np.poly1d(np.polyfit(args_x, args_y, len(args_x) - 1))

def plot_family(step, **kwargs): 
    EPS=kwargs.setdefault('eps', 0.001)
    min_z = kwargs.setdefault('min_z', step['data'][0]['z'])
    max_z = kwargs.setdefault('max_z', step['data'][-1]['z'])
    max_data = {'x': [], 'f': []}

    plt.clf()
    plt.xlabel(kwargs.setdefault('x_label', '$ x $'))
    plt.ylabel(kwargs.setdefault('y_label', '$ y $'))
    plt.grid(True)

    for i, row in enumerate(step['data']):
        if (((row['z'] >= min_z) and (row['z'] <= max_z)) or
            (math.fabs(max_z - row['z']) < EPS)): # float number equality
            plt.plot(row['x'], row['f'], 'r')
            max_data['x'].append(step['max']['x'][i])
            max_data['f'].append(step['max']['f'][i])

    plt.plot(max_data['x'], max_data['f'], 'bo-')

    # print 'NUM_OF_SERIES:', len(max_data['f'])

    if kwargs.setdefault('filename'):
        plt.savefig(kwargs['filename'])

def plot_opts(step, **kwargs):
    EPS=kwargs.setdefault('eps', 0.001)
    min_z = kwargs.setdefault('min_z', step['data'][0]['z'])
    max_z = kwargs.setdefault('max_z', step['data'][-1]['z'])
    z_data = []
    max_data = {'x': [], 'f': []}

    for i, row in enumerate(step['data']):
        if (((row['z'] >= min_z) and (row['z'] <= max_z)) or
            (math.fabs(max_z - row['z']) < EPS)): # float number equality 
            z_data.append(row['z'])
            max_data['x'].append(step['max']['x'][i])
            max_data['f'].append(step['max']['f'][i])

    plt.clf()
    plt.xlabel(kwargs.setdefault('x_label', '$ z $'))
    plt.ylabel(kwargs.setdefault('y_label', '$ x(z)/f(z) $'))
    plt.grid(True)
    plt.plot(z_data, max_data['x'], 'go-')
    plt.plot(z_data, max_data['f'], 'bo-')

    if kwargs.setdefault('filename'):
        plt.savefig(kwargs['filename'])

def export_value(value, filename):
    with open(filename, 'w') as f:
        if type(value) in [float, np.float64]:
            f.write('{:.4f}'.format(value))
        else:
            f.write(str(value))


### MAIN PROGRAM ###

RESOURCES=2
Z=my_range(0, 2, 0.01)
F=f
PREV_FUNCTION_OPTIMIZED=None
N_APPR_POINTS=8
N_ITER=5
EPS=0.005
STORAGE=[]

# backward pass
for step in range(N_ITER):
    step_data=generate(Z, F, PREV_FUNCTION_OPTIMIZED)

    # print 'MIN:', step, min_deposit(RESOURCES, N_ITER-step-1)
    # print 'MAX:', step, max_deposit(RESOURCES, N_ITER-step-1)
    # print

    plot_family(step_data,
                x_label='$ x_{} $'.format(str(N_ITER-step)),
                y_label='$ f_{} $'.format(str(N_ITER-step)),
                min_z=min_deposit(RESOURCES, N_ITER-step-1),
                max_z=max_deposit(RESOURCES, N_ITER-step-1),
                eps=EPS,
                filename='plot/family_{}.png'.format(str(N_ITER-step)))

    # print map(f_5o, z)
    # plt.show()

    plot_opts(step_data,
              x_label='$ z_{} $'.format(str(N_ITER-step-1)),
              y_label='$ x^*_{0}(z_{1})/f^*_{{0}}(z_{1}) $'.format(str(N_ITER-step), str(N_ITER-step-1)),
              min_z=min_deposit(RESOURCES, N_ITER-step-1),
              max_z=max_deposit(RESOURCES, N_ITER-step-1),
              eps=EPS,
              filename='plot/opts_{}.png'.format(str(N_ITER-step)))

    # plt.plot(z, map(f_5o, z))
    # plt.show()
    PREV_FUNCTION_OPTIMIZED = polyfit(Z, step_data['max']['f'], N_APPR_POINTS)
    STORAGE.append(step_data)

# straight pass
STORAGE.reverse()
cur_resources=RESOURCES

cur_row=my_index(STORAGE[0]['data'], cur_resources)

for i, step in enumerate(STORAGE):
    # print cur_row
    
    cur_x=step['max']['x'][cur_row]
    cur_y=cur_resources-cur_x
    cur_profit=step['max']['f'][cur_row]

    print '### STEP NO: {} ###'.format(str(i+1))
    print 'CURRENT RESOURCES:', cur_resources
    print 'CURRENT_X:', cur_x
    print 'CURRENT_Y:', cur_y
    print 'ACCUMULATED_PROFIT', cur_profit
    print

    export_value(cur_resources,
                 'values/resources_{}.tex'.format(i+1))
    export_value(cur_x,
                 'values/x_{}.tex'.format(i+1))
    export_value(cur_y,
                 'values/y_{}.tex'.format(i+1))
    export_value(cur_profit, 
                 'values/accumulated_profit_{}.tex'.format(i+1))

    cur_resources=0.75*cur_x+0.3*(cur_resources-cur_x)
    cur_row=my_index(step['data'], cur_resources, eps=EPS)

#     print step['max']['f'][s_row]

