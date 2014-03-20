set terminal jpeg
set output "images/scheme4.jpg"
set xrange[0:0.004]
set xlabel "t, с"
set ylabel "u, В"
plot 10 + 10.19*exp(-1428.6*x)*sin(7423.08*x - 1.38)
