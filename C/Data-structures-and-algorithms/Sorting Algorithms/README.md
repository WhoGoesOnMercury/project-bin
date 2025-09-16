## Sorting Algorithms

I suggest to go through the algorithms according to its numbering as I ordered it
according to my perception of its complexity in terms of implementation.

### Running the files

Again, there is an assumption that you have a working C compiler. To run any of 
the algorithms, simply run this command (just change algorithm_file_name.c to
your desired file):

`gcc "algorithm_file_name.c" -o main`

You will be greeted by a basic runtime summary of the algorithms. Do note that the 
runtime will vary because of the randomized nature of `data_loader.h`. 

Whenever we sort, we do not print any values nor should we place any print statements
within the loops. This can significantly bloat the runtime of the program and therefore
can affect more direct analysis. 

More specific cases will be added soon to allow for a greater analysis of the
sorting algorithms.
