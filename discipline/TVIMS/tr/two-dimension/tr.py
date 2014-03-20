import script.statistics as s

sample = {'x':[],
          'y':[]}

s.inputData(sample)
s.exportData(sample, 'val/sample.tex')

estimates = s.getEstimates(sample)
s.printEstimates(estimates)
print '~~~'

s.exportVal(estimates['x']['expectation'], 'val/x_expectation_value.tex')
s.exportVal(estimates['x']['expectationInt'][0], 'val/x_expectation_min.tex')
s.exportVal(estimates['x']['expectationInt'][1], 'val/x_expectation_max.tex')
s.exportVal(estimates['x']['dispersion'], 'val/x_dispersion_value.tex')
s.exportVal(estimates['x']['standartDeviation'], 'val/x_standart_deviation_value.tex')
s.exportVal(estimates['x']['dispersionInt'][0], 'val/x_dispersion_min.tex')
s.exportVal(estimates['x']['dispersionInt'][1], 'val/x_dispersion_max.tex')

s.exportVal(estimates['y']['expectation'], 'val/y_expectation_value.tex')
s.exportVal(estimates['y']['expectationInt'][0], 'val/y_expectation_min.tex')
s.exportVal(estimates['y']['expectationInt'][1], 'val/y_expectation_max.tex')
s.exportVal(estimates['y']['dispersion'], 'val/y_dispersion_value.tex')
s.exportVal(estimates['y']['standartDeviation'], 'val/y_standart_deviation_value.tex')
s.exportVal(estimates['y']['dispersionInt'][0], 'val/y_dispersion_min.tex')
s.exportVal(estimates['y']['dispersionInt'][1], 'val/y_dispersion_max.tex')

s.exportVal(estimates['corMoment'], 'val/correlation_moment.tex')
s.exportVal(estimates['corCoef'], 'val/correlation_coefficient_value.tex')

s.exportVal(estimates['corCoefIntA'], 'val/correlation_coefficient_a.tex')
s.exportVal(estimates['corCoefIntB'], 'val/correlation_coefficient_b.tex')
s.exportVal(estimates['corCoefInt'][0], 'val/correlation_coefficient_min.tex')
s.exportVal(estimates['corCoefInt'][1], 'val/correlation_coefficient_max.tex')

notCorHypothesisValue = s.checkNotCorHypothesis(estimates)

# Alpha == 0.05, n >= 50!
maxCorValue = 1.96
corConclusion = 'correlated!'
if notCorHypothesisValue < maxCorValue:
    corConclusion = 'not correlated!'
print 'No Correlation Hypothesis Value: {0:.4f}; Maximal: {1:.4f} => {2}'.format(
    notCorHypothesisValue, maxCorValue, corConclusion)
s.exportVal(notCorHypothesisValue, 'val/hypothesis_no_correlation.tex')
print '~~~'
regressionParams = s.getRegressionParams(estimates)
print 'Regression parameters: a_0 = {0:.4f}; a_1 = {1:.4f}'.format(
    regressionParams[0], regressionParams[1])
s.exportVal(regressionParams[0], 'val/regression_param_0.tex')
s.exportVal(regressionParams[1], 'val/regression_param_1.tex')

regressionFunction = s.getLinearFunction(regressionParams)
s.plotSampleOverlay(sample, regressionFunction, 'pic/sample_regression.png')
