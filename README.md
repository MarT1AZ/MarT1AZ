The file name is "openMP_ranksort.c"

To compile use the command "gcc -fopenmp -o openMP_ranksort openMP_ranksort.c"

To run use the command with the following format "./openMP_ranksort [num_thread] [num_data_size]"
For example
./openMP_ranksort 4 10000
./openMP_ranksort 12 200000


due to the limitation of the algorithm please use num_data_size lower than 500000
