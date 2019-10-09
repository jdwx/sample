# Sample

A simple C++ program for taking a random sample of lines from a file.

It uses the Knuth / Fisher-Yates shuffle.

It takes a filename for input, a number of sample lines to output and an optional "-h" flag to preserve one header line at the top of the file (which is then not counted as a sample line).

The order of lines is preserved from input to output.

Known to compile on FreeBSD 11.3 with Clang 8.

