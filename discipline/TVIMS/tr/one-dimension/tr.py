import script.statistics as s

sample = []

s.inputData(sample)
s.exportData(sample, 'val/sample.tex')

estimates = s.getEstimates(sample)
s.printEstimates(estimates)
print '~~~'

s.exportVal(estimates['expectation'], 'val/expectation_value.tex')
s.exportVal(estimates['expectationInt'][0], 'val/expectation_min.tex')
s.exportVal(estimates['expectationInt'][1], 'val/expectation_max.tex')
s.exportVal(estimates['dispersion'], 'val/dispersion_value.tex')
s.exportVal(estimates['standartDeviation'], 'val/standart_deviation_value.tex')
s.exportVal(estimates['dispersionInt'][0], 'val/dispersion_min.tex')
s.exportVal(estimates['dispersionInt'][1], 'val/dispersion_max.tex')

s.plotSample(sample, 'pic/sample.png')

statSeriesEqSize = s.getStatSeriesEqSize(sample)
print 'Equal-size statistical series:'
s.printStatSeries(statSeriesEqSize)
s.exportStatSeries(statSeriesEqSize, 'tbl/stat_series_eq_size.tex')
s.plotStatSeriesEqSize(statSeriesEqSize, 'pic/stat_series_eq_size.png')
print '~~~'

print 'Equal-probability statistical series:'
statSeriesEqProbability = s.getStatSeriesEqProbability(sample)
s.printStatSeries(statSeriesEqProbability)
s.exportStatSeries(statSeriesEqProbability, 'tbl/stat_series_eq_probability.tex')
s.plotStatSeriesEqProbability(statSeriesEqProbability, 'pic/stat_series_eq_probability.png')
print '~~~'

uniformDistribution = s.getUniformDistribution(estimates)
s.plotSampleOverlay(sample, uniformDistribution, 'pic/sample_uniform.png')
pirsonUniform = s.getPirson(statSeriesEqSize, uniformDistribution)
print 'Pirson criteria for uniform overlay:'
s.printPirson(pirsonUniform)
s.exportPirson(pirsonUniform, 'tbl/pirson_uniform.tex')
s.exportVal(pirsonUniform['sum'], 'val/pirson_uniform_sum.tex') 
s.exportVal(pirsonUniform['val'], 'val/pirson_uniform.tex') 
print 'pirsonUniform:', pirsonUniform['val']
print '~~~'

kolmogorovUniform = s.getKolmogorov(sample, uniformDistribution)
s.exportVal(kolmogorovUniform['lambda'], 'val/kolmogorov_uniform.tex')
s.exportVal(kolmogorovUniform['z'], 'val/kolmogorov_uniform_z.tex')
print 'kolmogorovUniform:', kolmogorovUniform['lambda']
print '~~~'

exponentialDistribution = s.getExponentialDistribution(estimates)
s.plotSampleOverlay(sample, exponentialDistribution, 'pic/sample_exponential.png')
pirsonExponential = s.getPirson(statSeriesEqSize, exponentialDistribution)
print 'Pirson criteria for exponential overlay:'
s.printPirson(pirsonExponential)
s.exportPirson(pirsonExponential, 'tbl/pirson_exponential.tex')
s.exportVal(pirsonExponential['sum'], 'val/pirson_exponential_sum.tex')
s.exportVal(pirsonExponential['val'], 'val/pirson_exponential.tex')
print 'pirsonExponential:', pirsonExponential['val']
print '~~~'

kolmogorovExponential = s.getKolmogorov(sample, exponentialDistribution)
s.exportVal(kolmogorovExponential['lambda'], 'val/kolmogorov_exponential.tex')
s.exportVal(kolmogorovExponential['z'], 'val/kolmogorov_exponential_z.tex')
print 'kolmogorovExponential:', kolmogorovExponential['lambda']
print '~~~'

normalDistribution = s.getNormalDistribution(estimates)
s.plotSampleOverlay(sample, normalDistribution, 'pic/sample_normal.png')
pirsonNormal = s.getPirson(statSeriesEqSize, normalDistribution)
print 'Pirson criteria for normal overlay:'
s.printPirson(pirsonNormal)
s.exportPirson(pirsonNormal, 'tbl/pirson_normal.tex')
s.exportVal(pirsonNormal['sum'], 'val/pirson_normal_sum.tex')
s.exportVal(pirsonNormal['val'], 'val/pirson_normal.tex')
print 'pirsonNormal:', pirsonNormal['val']
print '~~~'

kolmogorovNormal = s.getKolmogorov(sample, normalDistribution)
s.exportVal(kolmogorovNormal['lambda'], 'val/kolmogorov_normal.tex')
s.exportVal(kolmogorovNormal['z'], 'val/kolmogorov_normal_z.tex')
print 'kolmogorovNormal:', kolmogorovNormal['lambda']
print '~~~'
