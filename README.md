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

Run `periodTime` with `GENERATE_DISTRIBUTED_PERIOD` option set to `1` and copy _output.csv_ file in `./graphs` as _output_fill.csv_.

To generate graph in logarithmic scale with _non-distributed_ period run:
```bash
gnuplot -p smart_naive_log.gnuplot
```

To generate graph in logarithmic scale with _non-distributed_ period and area between min period and max period filled with color, run:
```bash
gnuplot -p smart_naive_log_fill.gnuplot
```

To generate graph in logarithmic scale with _distributed_ period run:
```bash
gnuplot -p smart_naive_log_dist.gnuplot
```

To generate graph in logarithmic scale with _non-distributed_ period and area between min period and max period filled with color, run:
```bash
gnuplot -p smart_naive_log_dist_fill.gnuplot
```
