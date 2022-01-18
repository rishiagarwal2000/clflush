# Clflush Benchmarking Code

## Installation requirements
* `gcc compiler`
* `python3, matplotlib, numpy`

## Code structure
* `clflush.c` contains code for benchmarking
    * Code has two parameters - `n`, `k`
    * `n` is size of array
    * `k` is number of random clflush executions
* `plot.py` contains code for plotting the output from `clflush.c`
    * It takes a command line argument `-d` or `--data` which has 4 choices - `hits`/`misses`/`r`/`w`
* `out/` contains all the output data from `clflush.c`
* `plots/` contains all the output data from `plot.py`
