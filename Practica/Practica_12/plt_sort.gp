set terminal qt  2 size 1200,800 enhanced font 'Helvetica,26'

set key left
set xtics 100000


set ylabel "Tiempo/ N log(N) [ns]"
set xlabel 'N  [10^7 x Tamaño del contenedor]'

set xra [1000:]
set format x "%2.0t"

log2(x) = log(x)/log(2)
plot "test.dat"   u ($1):(1*$2/($1*log($1))) w l  lw 2  lc rgb "red"   t "Lista:  > N log(N)"
replot "test.dat" u ($1):(1*$3/($1*log($1))) w l  lw 2  lc rgb "blue"  t "Deque:  \\~  N log(N)"
replot "test.dat" u ($1):(1*$4/($1*log($1))) w l  lw 2  lc rgb "black" t "Vector:  \\~ N log(N)"