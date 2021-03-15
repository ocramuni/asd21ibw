set datafile separator ','
set title 'Tempi di calcolo del periodo con algoritmo naive (periodo distribuito)'
set xlabel 'Lunghezza stringa'
set ylabel 'Tempo (s)'
set term qt size 1600,800
plot "output_dist.csv" using 1:6 with linespoint pt 5 ps 0.5 title "Naive"
