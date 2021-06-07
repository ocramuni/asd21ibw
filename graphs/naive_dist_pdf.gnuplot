set datafile separator ','
#set title 'Tempi di calcolo del periodo con algoritmo naive (periodo distribuito)'
set xlabel 'Lunghezza stringa'
set ylabel 'Tempo (s)'
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'naive_dist.pdf'
plot "output_dist.csv" using 1:6 with linespoint pt 5 ps 0.3 title "Naive"
