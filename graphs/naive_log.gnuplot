set datafile separator ','
set title 'Tempi di calcolo del periodo con algoritmo naive (periodo non distribuito)'
set xlabel 'Lunghezza stringa'
set ylabel 'Tempo'
set logscale xy
set term qt size 1600,800
plot "output.csv" using 1:6 with linespoint pt 5 ps 0.5 title "Naive"
