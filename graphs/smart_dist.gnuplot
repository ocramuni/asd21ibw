set datafile separator ','
set title 'Tempi di calcolo del periodo con algoritmo smart (periodo distribuito)'
set xlabel 'Lunghezza stringa'
set ylabel 'Tempo (ns)'
set key right bottom
set term qt size 1600,800
plot "output_dist.csv" using 1:3 with linespoints pt 5 ps 0.5 title "Smart"
