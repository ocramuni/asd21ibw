# Code
## To configure:
```bash 
cmake -S . -B cmake-build-debug 
```

## To build:
```bash
cmake --build cmake-build-debug
```

## To run:
```bash
./cmake-build-debug/apps/periodTime
```

# Graphs
## To generate graphs:
Run `periodTime` with `GENERATE_DISTRIBUTED_PERIOD` option set to `0` and copy _output.csv_ file in `./graphs`.

Run `periodTime` with `GENERATE_DISTRIBUTED_PERIOD` option set to `1` and copy _output.csv_ file in `./graphs` as _output_dist.csv_.

To generate graphs to compare execution time, run:

- `gnuplot -p smart_naive.gnuplot` : graph in linear scale with _non-distributed_ period
- `gnuplot -p smart_naive_dist.gnuplot` : graph in linear scale with _distributed_ period
- `gnuplot -p smart_naive_log.gnuplot` : graph in logarithmic scale with _non-distributed_ period
- `gnuplot -p smart_naive_log_dist.gnuplot` : graph in logarithmic scale with _distributed_ period

To generate graphs of smart algorithm, run:

- `gnuplot -p smart.gnuplot` : graph in linear scale with _non-distributed_ period
- `gnuplot -p smart_dist.gnuplot` : graph in linear scale with _distributed_ period
- `gnuplot -p smart_log.gnuplot` : graph in logarithmic scale with _non-distributed_ period
- `gnuplot -p smart_log_dist.gnuplot` : graph in logarithmic scale with _distributed_ period

To generate graphs of naive algorithm, run:

- `gnuplot -p naive.gnuplot` : graph in linear scale with _non-distributed_ period
- `gnuplot -p naive_dist.gnuplot` : graph in linear scale with _distributed_ period
- `gnuplot -p naive_log.gnuplot` : graph in logarithmic scale with _non-distributed_ period
- `gnuplot -p naive_log_dist.gnuplot` : graph in logarithmic scale with _distributed_ period

## To generate report images
To generate all pdf files needed to compile report, move to `./graphs` and run:

```bash
./generate_figures.sh
```

then copy all pdf files to `./report/images`.

# Report
## Compile report:

Generate graphs and copy them to `./report/images`. To compile report, move to `./report` and run:

```bash
pdflatex report.tex
```
