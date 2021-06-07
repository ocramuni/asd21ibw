set datafile separator ','
#set title 'Tempi di calcolo del periodo con algoritmo smart (periodo distribuito)'
set xlabel 'Lunghezza stringa'
set ylabel 'Tempo (ns)'
set key right bottom
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'smart_dist.pdf'
plot "output_dist.csv" using 1:3 with linespoints pt 5 ps 0.3 lc 2 title "Smart"
