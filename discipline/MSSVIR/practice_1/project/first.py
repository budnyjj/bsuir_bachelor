#!/usr/bin/python

import sys

# file format:
# units
# student value
# confidence interval
# values
# ...

try:
	filename = sys.argv[1]
except:
	print 'Using: python <this script> <filename>'
	exit()

file = open(filename)

units = file.readline()
student = float(file.readline())
pd = float(file.readline())

X = file.readlines()

file.close()

sum = 0

for x in X:
	sum += float(x)

average = sum/len(X)
print 'average x: ', average

sum_squares = 0

print 'Vi \t Vi^2'
for x in X:
	v = abs(float(x) - average)
	v_square = v ** 2
	print '{0:.4f} \t {1:.4f}'.format(v, v_square)
	sum_squares += v_square

SKO = pow(sum_squares/(len(X)-1), 0.5)
print 'SKO: ', SKO

for x in X:
	if abs(float(x) - average) >= 3*SKO:
		print 'imeetsya grubaya pogreshnost\':', x
		print 'udalite', x, ' iz uslovia'
		quit()

SKP = SKO/pow(len(X), 0.5)
print 'SKP: ', SKP

di = float(student)*SKP

print 'otvet: x = ({0:.3f} +- {1:.3f}) {2:s} Pd = {3:.2f}'.format(average, di, units, pd)   
exit()
