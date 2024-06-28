## Compilation with MinGW:

cd build
cmake -G "MinGW Makefiles" ..
mingw32-make

## Execution

dev.exe path alg s t

Where : 
- path is the string for loading the graph
- alg is the choice of the alg : 0 for FIFO, 1 for Hyper volume
- s is the source node
- t is the objective node

Example : dev.exe "../save/temp/small_graph" 0 0 3