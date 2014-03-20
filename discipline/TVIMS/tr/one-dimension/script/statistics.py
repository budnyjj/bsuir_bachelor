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
                data.append(float(line))
    except:
        print "Usage: tr.py <filename>"
        sys.exit(0)
    
    return data.sort()

def getEstimates(data):
    estimates = {}
    numData = float(len(data))

    expValue = 0
    for x in data:
        expValue += x
    expValue /= numData
    estimates['expectation'] = expValue

    dispValue = 0
    for x in data:
        dispValue += x**2
    dispValue /= numData - 1
    dispValue -= numData * (expValue ** 2) / (numData - 1)
    estimates['dispersion'] = dispValue
    estimates['standartDeviation'] = math.sqrt(dispValue)

    # reliability = 0.95
    zGamma = 1.96

    expDelta = zGamma*math.sqrt(dispValue/numData)
    estimates['expectationInt'] = (expValue - expDelta, expValue + expDelta)

    dispDelta = zGamma * math.sqrt(2 / (numData - 1)) * dispValue
    estimates['dispersionInt'] = (dispValue - dispDelta, dispValue + dispDelta)

    return estimates

def getStatSeriesEqSize(data):
    statSeries = []
    numInt = 0
    dataNum = len(data)
    if dataNum <= 100:
        numInt = int(math.sqrt(dataNum))
    else:
        numInt = int(2*math.log10(dataNum))

    lengthInt = (data[-1] - data[0]) / numInt

    startInt = data[0]
    endInt = startInt + lengthInt

    for i in xrange(numInt):
        curSubInfo = {'start': startInt,
                      'end': endInt,
                      'length': lengthInt}
        if i != numInt:
            curSubInfo['series'] = [x for x in data \
                                    if x >= startInt and x < endInt ]
        else:
            curSubInfo['series'] = [x for x in data \
                                    if x >= startInt and x <= endInt ]
        curSubInfo['num'] = len(curSubInfo['series'])
        curSubInfo['freq'] = float(curSubInfo['num']) / dataNum
        curSubInfo['statProbDensity'] = curSubInfo['freq'] / curSubInfo['length']

        statSeries.append(curSubInfo)
        
        startInt = endInt
        endInt += lengthInt
        
    return statSeries

def getStatSeriesEqProbability(data):
    statSeries = []
    numInt = 0
    dataNum = len(data)
    if dataNum <= 100:
        numInt = int(math.sqrt(dataNum))
    else:
        numInt = int(2*math.log10(dataNum))

    sizeInt = dataNum / numInt

    for i in xrange(numInt):
        curSubInfo = {}
        if i == 0:
            curSubInfo['series'] = data[0:sizeInt]
            curSubInfo['start'] = curSubInfo['series'][0]
        else:
            curSubInfo['series'] = data[i*sizeInt : (i + 1)*sizeInt]
            curSubInfo['start'] = statSeries[-1]['end']
        # print curSubInfo

        if i == numInt - 1:
            curSubInfo['end'] = curSubInfo['series'][-1]
        else: 
            curSubInfo['end'] = (curSubInfo['series'][-1] + data[(i + 1)*sizeInt]) / 2

        curSubInfo['length'] = curSubInfo['end'] - curSubInfo['start']
        curSubInfo['num'] = len(curSubInfo['series'])
        curSubInfo['freq'] = float(curSubInfo['num']) / dataNum
        curSubInfo['statProbDensity'] = curSubInfo['freq'] / curSubInfo['length']

        statSeries.append(curSubInfo)

    return statSeries

def getUniformDistribution(estimates):
    def uniformDistribution(x):
        a = estimates['expectation'] - math.sqrt(3*estimates['dispersion'])
        b = estimates['expectation'] + math.sqrt(3*estimates['dispersion'])
        if x < a:
            return 0
        elif a <= x <= b:
            return (x - a)/float(b - a)
        else:
            return 1
    return uniformDistribution

def getExponentialDistribution(estimates):
    l = 1/estimates['expectation']
    def exponentialDistribution(t):
        if t <= 0:
            return 0
        else:
            return 1-math.exp(-1*l*t)
    return exponentialDistribution

def getNormalDistribution(estimates):
    m = estimates['expectation']
    s = math.sqrt(estimates['dispersion'])
    f = lambda x, m, s: \
        1/(s*math.sqrt(2*math.pi))*math.exp(-1*((x-m)**2)/(2*(s**2)))

    # integral table
    valsX = []
    x = -100
    dx = 0.01
    while x <= 100:
        valsX.append(x)
        x += dx
    del x

    tblDensityF = {}
    minX = valsX[0]
    minXS = '{0:.2f}'.format(minX)
    # convert x to str!
    tblDensityF[minXS] = f(minX, m, s)
    for x in valsX[1:]:
        tblDensityF['{0:.2f}'.format(x)] = f(x, m, s) - tblDensityF[minXS]
    tblDensityF['-0.00'] = tblDensityF['0.00'] # fix -0.00

    tblF = {}
    tblF[minXS] = 0
    for x in valsX[1:]:
        xS = '{0:.2f}'.format(x)
        prevXS = '{0:.2f}'.format(x - dx)
        tblF[xS] = math.fabs(tblDensityF[xS] + tblDensityF[prevXS]) * dx / 2 + \
                   tblF[prevXS] 
    tblF['-0.00'] = tblF['0.00'] # fix -0.00

    def normalDistribution(x):
        return tblF['{0:.2f}'.format(x)]

    return normalDistribution

def getPirson(seriesEqSize, overlayFunc):
    ''' returns hi^2 or INF if cannot calculate '''
    pirson = {'val': '+INF',
              'sum': '+INF',
              'data': [], }

    seriesSize = 0
    hi = 0
    for j, interval in enumerate(seriesEqSize):
        startInt = 0
        endInt = 0
        fStartInt = 0
        fEndInt = 0
        if j == 0:
            startInt = '-INF'
            endInt = interval['end']
            
            fStartInt = 0
            fEndInt = overlayFunc(endInt)
        elif j == len(seriesEqSize) - 1:
            startInt = interval['start']
            endInt = '+INF'

            fStartInt = overlayFunc(startInt)
            fEndInt = 1 
        else:
            startInt = interval['start']
            endInt = interval['end']

            fStartInt = overlayFunc(startInt)
            fEndInt = overlayFunc(endInt)
        tDensity = fEndInt - fStartInt
        rDensity = interval['freq']

        # print startInt, ":", endInt
        # print fStartInt, ":", fEndInt
        # print tDensity
        # print 

        curSubInfo = {'start': startInt,
                      'end': endInt,
                      'fStart': fStartInt,
                      'fEnd': fEndInt,
                      'freq': rDensity,
                      'density': tDensity,}

        try:
            pirsonPartVal = ((tDensity - rDensity) ** 2) / tDensity
        except ZeroDivisionError: # tDensity == 0
            curSubInfo['pirsonPart'] = '+INF'
            pirson['data'].append(curSubInfo)
            return pirson
        else:
            curSubInfo['pirsonPart'] = pirsonPartVal
            hi += pirsonPartVal

        pirson['data'].append(curSubInfo)
        seriesSize += interval['num']

    pirson['sum'] = hi
    hi *= seriesSize
    pirson['val'] = hi
    return pirson

def getKolmogorov(data, overlayFunc):
    z = 0
    dataNum = float(len(data))
    for i, x in enumerate(data):
        diff = math.fabs((i+1)/dataNum - overlayFunc(x))
        if z < diff:
            z = diff
    l = z * math.sqrt(dataNum)
    return {'z': z, 'lambda': l}

def printStatSeries(series):
    totalNum = 0
    totalLength = 0
    freqSum = 0

    print '|' + ''.join(['-' for i in range(72)]) + '|'

    print '|{0:6}|{1:10}|{2:10}|{3:10}|{4:10}|{5:10}|{6:10}|'.format(
        'j'.center(3), 'A_j'.center(10), 'B_j'.center(10), 'h_j'.center(10),
        'v_j'.center(10), 'p*_j'.center(10), 'f*_j'.center(10))

    print '|' + ''.join(['-' for i in range(72)]) + '|'

    for j, interval in enumerate(series):
        totalNum += interval['num']
        totalLength += interval['length']
        freqSum += interval['freq']

        print '|{0:6}|{1:10.3f}|{2:10.3f}|{3:10.3f}|{4:10}|{5:10.4f}|{6:10.4f}|'.format(
            j + 1, interval['start'], interval['end'], interval['length'],
            interval['num'], interval['freq'], interval['statProbDensity'])
        
    print '|' + ''.join(['-' for i in range(72)]) + '|'

    print '|{0:4}|{1:10}|{2:10}|{3:10.3f}|{4:10}|{5:10.4f}|{6:10}|'.format(
        'total:', '', '', totalLength, totalNum, freqSum, '')

    print '|' + ''.join(['-' for i in range(72)]) + '|\n'

def printEstimates(estimates):
    print 'm*_x = {0:.4f};\tI*_m = [{1:.4f}; {2:.4f}]'.format(
        estimates['expectation'],
        estimates['expectationInt'][0],
        estimates['expectationInt'][1])

    print 'D*_x = {0:.4f};\tI*_d = [{1:.4f}; {2:.4f}]'.format(
        estimates['dispersion'],
        estimates['dispersionInt'][0],
        estimates['dispersionInt'][1])
    print

def printPirson(pirson):
    freqSum = 0
    densitySum = 0
    pirsonPartSum = 0
    print '|' + ''.join(['-' for i in range(72)]) + '|'

    print '|{0:3}|{1:7}|{2:7}|{3:7}|{4:7}|{5:7}|{6:6}|{7:21}|'.format(
        'j'.center(3), 'A_j'.center(7), 'B_j'.center(7),
        'F0(A_j)'.center(7), 'F0(B_j)'.center(7),
        'p_j'.center(7), 'p*_j'.center(6), '((p*_j-p_j)^2)/p_j'.center(21))

    print '|' + ''.join(['-' for i in range(72)]) + '|'
    
    pirsonDataSize = len(pirson['data'])
    for j, interval in enumerate(pirson['data']):
        freqSum += interval['freq']
        densitySum += interval['density']
        if interval['pirsonPart'] != '+INF':
            if j == 0:
                print '|{0:3}|{1:7}|{2:7.3f}|{3:7.4f}|{4:7.4f}|{5:7.4f}|{6:6.4f}|{7:21.4f}|'.format(
                    j + 1, '-INF'.rjust(7), interval['end'], interval['fStart'], interval['fEnd'],
                    interval['density'], interval['freq'], interval['pirsonPart'])
            elif j == pirsonDataSize - 1:
                print '|{0:3}|{1:7.3f}|{2:7}|{3:7.4f}|{4:7.4f}|{5:7.4f}|{6:6.4f}|{7:21.4f}|'.format(
                    j + 1, interval['start'], '+INF'.rjust(7), interval['fStart'], interval['fEnd'],
                    interval['density'], interval['freq'], interval['pirsonPart'])
            else: 
                print '|{0:3}|{1:7.3f}|{2:7.3f}|{3:7.4f}|{4:7.4f}|{5:7.4f}|{6:6.4f}|{7:21.4f}|'.format(
                    j + 1, interval['start'], interval['end'], interval['fStart'], interval['fEnd'],
                    interval['density'], interval['freq'], interval['pirsonPart'])
            pirsonPartSum += interval['pirsonPart']
        else:
            if j == 0:
                print '|{0:3}|{1:7}|{2:7.3f}|{3:7.4f}|{4:7.4f}|{5:7.4f}|{6:6.4f}|{7:21}|'.format(
                    j + 1, '-INF'.rjust(7), interval['end'], interval['fStart'], interval['fEnd'],
                    interval['density'], interval['freq'], interval['pirsonPart'].rjust(21))
            elif j == pirsonDataSize - 1:
                print '|{0:3}|{1:7.3f}|{2:7}|{3:7.4f}|{4:7.4f}|{5:7.4f}|{6:6.4f}|{7:21}|'.format(
                    j + 1, interval['start'], '+INF'.rjust(7)
                    , interval['fStart'], interval['fEnd'],
                    interval['density'], interval['freq'], interval['pirsonPart'].rjust(21))
            else: 
                print '|{0:3}|{1:7.3f}|{2:7.3f}|{3:7.4f}|{4:7.4f}|{5:7.4f}|{6:6.4f}|{7:21}|'.format(
                    j + 1, interval['start'], interval['end'], interval['fStart'], interval['fEnd'],
                    interval['density'], interval['freq'], interval['pirsonPart'].rjust(21))
            pirsonPartSum = '+INF'
                
    print '|' + ''.join(['-' for i in range(72)]) + '|'

    if pirsonPartSum != '+INF':
        print '|{0:3}|{1:7}|{2:7}|{3:7}|{4:7}|{5:7.4f}|{6:6.4f}|{7:21.4f}|'.format(
            '', '', '', '',
            'total'.center(7), freqSum, densitySum, pirsonPartSum)
    else:
        print '|{0:3}|{1:7}|{2:7}|{3:7}|{4:7}|{5:7.4f}|{6:6.4f}|{7:21}|'.format(
            '', '', '', '',
            'total'.center(7), freqSum, densitySum, pirsonPartSum.rjust(21))

    print '|' + ''.join(['-' for i in range(72)]) + '|'

    print

def exportData(data, filename, numCols=10):
    numData = len(data)
    numRows = int(numData/float(numCols) + 1)
    with open(filename, 'w') as f:
        for i in xrange(numRows):
             if (i+1)*numCols < numData:
                 dataRow = '\t& '.join(str(x) for x in data[i * numCols: (i+1)*numCols])
             else:
                 dataRow = '\t& '.join(str(x) for x in data[i * numCols:])
             f.write(dataRow + '\t\\\\ \n')

def exportStatSeries(series, filename):
    totalNum = 0
    totalLength = 0
    freqSum = 0

    with codecs.open(filename, encoding='utf-8', mode='w') as f:
        tblTitle = '\t& '.join(['$ j $', '$ A_j $', '$ B_j $', '$ h_j $', '$ v_j $', '$ p^{*}_j $', '$ f^{*}_j $'])

        f.write(tblTitle + ' \\\\ \\hline\n')
        for j, interval in enumerate(series):
            totalNum += interval['num']
            totalLength += interval['length']
            freqSum += interval['freq']

            tblRow = '\t& '.join([
                str(j + 1),
                '{0:.3f}'.format(interval['start']), '{0:.3f}'.format(interval['end']),
                '{0:.3f}'.format(interval['length']), str(interval['num']),
                '{0:.4f}'.format(interval['freq']), '{0:.4f}'.format(interval['statProbDensity'])])
            f.write(tblRow + ' \\\\ \\hline\n')

        totalRow = '\t&'.join([u'Всего:', '', '', '{0:.3f}'.format(totalLength), str(totalNum), '{0:.4f}'.format(freqSum), ''])
        f.write(totalRow + ' \\\\ \\hline\n')

def exportPirson(pirson, filename):
    freqSum = 0
    densitySum = 0
    pirsonPartSum = 0
    with codecs.open(filename, encoding='utf-8', mode='w') as f:
        tblTitle = '\t& '.join(
            [ '$ j $', '$ A_j $', '$ B_j $', '$ F_0(A_j) $',
              '$ F_0(B_j) $', '$ p_j $', '$ p_j^{*} $', '$ \\frac{(p^{*}_j - p_j)^2}{p_j} $'])
        f.write(tblTitle + ' \\\\ \\hline\n')
   
        pirsonDataSize = len(pirson['data'])
        for j, interval in enumerate(pirson['data']):
            freqSum += interval['freq']
            densitySum += interval['density']
            

            if interval['pirsonPart'] != '+INF':
                if j == 0:
                    tblRow = '\t& '.join([ str(j + 1),
                                           '$ -\\infty $', '{0:.3f}'.format(interval['end']),
                                           '{0:.4f}'.format(interval['fStart']), '{0:.4f}'.format(interval['fEnd']),
                                           '{0:.4f}'.format(interval['density']), '{0:.4f}'.format(interval['freq']),
                                           '{0:.4f}'.format(interval['pirsonPart']),
                                       ])
                elif j == pirsonDataSize - 1:
                    tblRow = '\t& '.join([ str(j + 1),
                                           '{0:.3f}'.format(interval['start']), '$ +\\infty $',
                                           '{0:.4f}'.format(interval['fStart']), '{0:.4f}'.format(interval['fEnd']),
                                           '{0:.4f}'.format(interval['density']), '{0:.4f}'.format(interval['freq']),
                                           '{0:.4f}'.format(interval['pirsonPart']),
                                       ])
                else: 
                    tblRow = '\t& '.join([ str(j + 1),
                                           '{0:.3f}'.format(interval['start']), '{0:.3f}'.format(interval['end']),
                                           '{0:.4f}'.format(interval['fStart']), '{0:.4f}'.format(interval['fEnd']),
                                           '{0:.4f}'.format(interval['density']), '{0:.4f}'.format(interval['freq']),
                                           '{0:.4f}'.format(interval['pirsonPart']),
                                       ])
                pirsonPartSum += interval['pirsonPart']
            else:
                if j == 0:
                    tblRow = '\t& '.join([ str(j + 1),
                                           '$ -\\infty $', '{0:.3f}'.format(interval['end']),
                                           '{0:.4f}'.format(interval['fStart']), '{0:.4f}'.format(interval['fEnd']),
                                           '{0:.4f}'.format(interval['density']), '{0:.4f}'.format(interval['freq']),
                                           '$ +\\infty $',
                                       ])
                elif j == pirsonDataSize - 1:
                    tblRow = '\t& '.join([ str(j + 1),
                                           '{0:.3f}'.format(interval['start']), '$ +\\infty $',
                                           '{0:.4f}'.format(interval['fStart']), '{0:.4f}'.format(interval['fEnd']),
                                           '{0:.4f}'.format(interval['density']), '{0:.4f}'.format(interval['freq']),
                                           '$ +\\infty $',
                                       ])
                else: 
                    tblRow = '\t& '.join([ str(j + 1),
                                           '{0:.3f}'.format(interval['start']), '{0:.3f}'.format(interval['end']),
                                           '{0:.4f}'.format(interval['fStart']), '{0:.4f}'.format(interval['fEnd']),
                                           '{0:.4f}'.format(interval['density']), '{0:.4f}'.format(interval['freq']),
                                           '$ +\\infty $',
                                       ])
                pirsonPartSum = '+INF'

            f.write(tblRow + ' \\\\ \\hline\n')

        if pirsonPartSum != '+INF':
            totalRow = '\t&'.join(['', '', '', '', u'Всего:', '{0:.4f}'.format(freqSum),
                                   '{0:.4f}'.format(densitySum), '{0:.4f}'.format(pirsonPartSum)
                               ])
        else:
            totalRow = '\t&'.join(['', '', '', '', u'Всего:', '{0:.4f}'.format(freqSum),
                                   '{0:.4f}'.format(densitySum), '$ +\infty $'
                               ])
        f.write(totalRow + ' \\\\ \\hline\n')
                        	
def exportVal(val, filename):
    with open(filename, 'w') as f:
        if type(val) is float:
            f.write('{0:.4f}'.format(val))
        else:
            f.write(val)


def plotSample(data, filename):
    l = float(len(data))
    plt.plot(data, [(i + 1)/l for i, x in enumerate(data)], linestyle='steps')
    plt.xlabel('$ x $')
    plt.ylabel('$ p^{*}(x) $')
    plt.grid(True)
    plt.savefig(filename)
    plt.clf()

def plotSampleOverlay(data, overlayFunc, filename):
    l = float(len(data))
    plt.plot(data, [i/l for i, x in enumerate(data)], linestyle='steps')
    
    overlayData = []
    dx = 0.01
    x = data[0]
    while x <= data[-1]:
        overlayData.append(x)
        x += dx

    plt.plot(overlayData, [overlayFunc(x) for x in overlayData])

    plt.xlabel('$ x $')
    plt.ylabel('$ p(x) $')
    plt.grid(True)
    plt.savefig(filename)
    plt.clf()

def plotStatSeriesEqSize(series, filename):
    histData = []
    for interval in series:
        histData.extend(interval['series'])
    plt.hist(histData, normed=True)
    plt.xlabel('$ x $')
    plt.ylabel('$ f^{*}(x) $')
    plt.grid(True)
    plt.savefig(filename)
    plt.clf()

def plotStatSeriesEqProbability(series, filename):
    histData = []
    histIntervals = []
    for interval in series:
        histData.extend(interval['series'])
        histIntervals.append(interval['start'])
    histIntervals.append(series[-1]['end'])

    plt.hist(histData, bins=histIntervals, normed=True)
    plt.xlabel('$ x $')
    plt.ylabel('$ f^{*}(x) $')
    plt.grid(True)
    plt.savefig(filename)
    plt.clf()
