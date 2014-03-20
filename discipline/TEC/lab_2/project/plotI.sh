set terminal jpeg
set output "images/scheme3.jpg"
set xrange[0:0.004]
set xlabel "t, с"
set ylabel "i, A"
plot 0.01*exp(-1428.6*x)*sin(7423.08*x)
