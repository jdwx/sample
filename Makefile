
sample: sample.o
	c++ -o sample sample.o

sample.o: sample.cc
	c++ -g -O -Weverything -Wno-c++98-compat -c sample.cc

test: sample
	./sample -h test.txt 5
	./sample -h test.txt 10

prod: sample
	time ./sample -h /data/jdw/gps.csv 1000000 >/data/jdw/gps1m.csv


