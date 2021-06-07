#!/usr/bin/env bash

for g in $(ls -1 *pdf.gnuplot)
do
	gnuplot -p $g
done
