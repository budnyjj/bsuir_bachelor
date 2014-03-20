# -*- coding: utf-8 -*-

import sys
import math
import matplotlib.pyplot as plt
import codecs
from matplotlib import rc

rc('font',**{'family':'serif','serif':['Palatino']})
rc('text', usetex=True)

def inputData(data):
    filename = ""
    try:
        filename = sys.argv[1]
        with open(filename) as f:
            for line in f:
                (x, y) = line.split(';')
                data['x'].append(float(x))
                data['y'].append(float(y))
    except:
        print "Usage: tr.py <filename>"
        sys.exit(0)

    return data

def getEstimates(data):
    estimates = {'x': {},
                 'y': {},
                 'corCoefInt': []}

    divideF = lambda x, y: (x, y)
    points =  map(divideF, data['x'], data['y'])
    numPoints = float(len(points))
    estimates['numPoints'] = numPoints

    expValueX = 0
    expValueY = 0
    for pair in points:
        expValueX += pair[0]
        expValueY += pair[1]
    expValueX /= numPoints
    expValueY /= numPoints
    estimates['x']['expectation'] = expValueX
    estimates['y']['expectation'] = expValueY

    dispValueX = 0
    dispValueY = 0
    for pair in points:
        dispValueX += pair[0]**2
        dispValueY += pair[1]**2
    dispValueX /= numPoints - 1
    dispValueY /= numPoints - 1

    dispValueX -= numPoints * (expValueX ** 2) / (numPoints - 1)
    dispValueY -= numPoints * (expValueY ** 2) / (numPoints - 1)

    estimates['x']['dispersion'] = dispValueX
    estimates['y']['dispersion'] = dispValueY

    estimates['x']['standartDeviation'] = math.sqrt(dispValueX)
    estimates['y']['standartDeviation'] = math.sqrt(dispValueY)

    # reliability = 0.95
    zGamma = 1.96

    expDeltaX = zGamma*math.sqrt(dispValueX/numPoints)
    expDeltaY = zGamma*math.sqrt(dispValueY/numPoints)

    estimates['x']['expectationInt'] = (expValueX - expDeltaX, expValueX + expDeltaX)
    estimates['y']['expectationInt'] = (expValueY - expDeltaY, expValueY + expDeltaY)
                                        
    dispDeltaX = zGamma * math.sqrt(2 / (numPoints - 1)) * dispValueX
    dispDeltaY = zGamma * math.sqrt(2 / (numPoints - 1)) * dispValueY

    estimates['x']['dispersionInt'] = (dispValueX - dispDeltaX, dispValueX + dispDeltaX)
    estimates['y']['dispersionInt'] = (dispValueY - dispDeltaY, dispValueY + dispDeltaY)

    corMoment = 0
    for pair in points:
        corMoment += (pair[0] - expValueX)*(pair[1] - expValueY)
    corMoment /= numPoints - 1
    estimates['corMoment'] = corMoment

    corCoef = corMoment / math.sqrt(dispValueX*dispValueY)
    estimates['corCoef'] = corCoef
    
    a = 0.5 * math.log((1 + corCoef) / (1 - corCoef)) - zGamma / math.sqrt(numPoints - 3)
    b = 0.5 * math.log((1 + corCoef) / (1 - corCoef)) + zGamma / math.sqrt(numPoints - 3)
    
    estimates['corCoefIntA'] = a
    estimates['corCoefIntB'] = b

    estimates['corCoefInt'].append((math.exp(2*a) - 1)/(math.exp(2*a) + 1))
    estimates['corCoefInt'].append((math.exp(2*b) - 1)/(math.exp(2*b) + 1))

    return estimates

def getRegressionParams(estimates):
    params = {}
    params[1] = estimates['corMoment']/estimates['x']['dispersion']
    params[0] = estimates['y']['expectation'] - params[1]*estimates['x']['expectation']
    return params

def getLinearFunction(params):
    def linearFunction(x):
        return params[0] + params[1] * x

    return linearFunction

def checkNotCorHypothesis(estimates):
    notCorValue = 0
    if estimates['numPoints'] < 50:
        notCorValue = math.fabs(estimates['corCoef']) * math.sqrt(estimates['numPoints'] - 2)
    else:
        notCorValue = math.fabs(estimates['corCoef']) * math.sqrt(estimates['numPoints'])
    notCorValue /= math.sqrt(1-(estimates['corCoef'])**2)
    return notCorValue


def printEstimates(estimates):
    print 'm*_x = {0:.4f};\tI*_m_x = [{1:.4f}; {2:.4f}]'.format(
        estimates['x']['expectation'],
        estimates['x']['expectationInt'][0],
        estimates['x']['expectationInt'][1])
    print 'D*_x = {0:.4f};\tI*_d_x = [{1:.4f}; {2:.4f}]'.format(
        estimates['x']['dispersion'],
        estimates['x']['dispersionInt'][0],
        estimates['x']['dispersionInt'][1])
    print 
    print 'm*_y = {0:.4f};\tI*_m_y = [{1:.4f}; {2:.4f}]'.format(
        estimates['y']['expectation'],
        estimates['y']['expectationInt'][0],
        estimates['y']['expectationInt'][1])
    print 'D*_y = {0:.4f};\tI*_d_y = [{1:.4f}; {2:.4f}]'.format(
        estimates['y']['dispersion'],
        estimates['y']['dispersionInt'][0],
        estimates['y']['dispersionInt'][1])
    print
    print 'K*_xy = {0:.4f}'.format(estimates['corMoment'])
    print 'R*_xy = {0:.4f};\tI(R*_xy) = [{1:.4f}; {2:.4f}]'.format(
        estimates['corCoef'], estimates['corCoefInt'][0], estimates['corCoefInt'][1])
    print

def exportData(data, filename, numCols=5):
    divideF = lambda x, y: (x, y)
    points =  map(divideF, data['x'], data['y'])
    numPoints = len(points)
    numRows = int(numPoints/float(numCols) + 1)

    with open(filename, 'w') as f:
        for i in xrange(numRows):
             if (i+1)*numCols < numPoints:
                 dataRow = '\t& '.join(
                     '({0:.2f}; {1:.2f})'.format(pair[0], pair[1]) 
                     for pair in points[i * numCols: (i+1)*numCols])
             else:
                 dataRow = '\t& '.join(
                     '({0:.2f}; {1:.2f})'.format(pair[0], pair[1]) 
                     for pair in points[i * numCols:])
             f.write(dataRow + '\t\\\\ \n')
                        	
def exportVal(val, filename):
    with open(filename, 'w') as f:
        if type(val) is float:
            f.write('{0:.4f}'.format(val))
        else:
            f.write(val)

def plotSampleOverlay(data, overlayFunc, filename):
    overlayData = {'x': [],
                   'y': []}
    minX = min(data['x'])
    maxX = max(data['x'])
    dx = 0.01
    x = minX
    while x <= maxX:
        overlayData['x'].append(x)
        x += dx
    
    overlayData['y'] = map(overlayFunc, overlayData['x'])
    
    plt.plot(data['x'], data['y'], 'ro')
    plt.plot(overlayData['x'], overlayData['y'])

    plt.xlabel('$ x $')
    plt.ylabel('$ y $')
    plt.grid(True)
    plt.savefig(filename)
    plt.clf()

