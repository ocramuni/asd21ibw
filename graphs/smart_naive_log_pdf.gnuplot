set datafile separator ','
#set title 'Confronto tempi di calcolo del periodo tra algoritmo smart e algoritmo naive (periodo non distribuito)'
set xlabel 'Lunghezza stringa'
set ylabel 'Tempo'
set logscale xy
set terminal pdf size 21cm,10cm enhanced color rounded \
    font 'Helvetica,12'
set output 'smart_naive_log.pdf'
plot "output.csv" using 1:3 with linespoints pt 5 ps 0.3 title "Smart", "" using 1:6 with linespoint pt 5 ps 0.3 title "Naive"
