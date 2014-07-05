all: skynet2 

skynet: skynet.cc
	g++ -Wall -ftemplate-depth-2000000 -ftemplate-backtrace-limit=0 -o $@ $@.cc

skynet2: skynet2.cc
	g++ -O3 -Wall -o $@ $@.cc

clean: 
	rm -f skynet skynet2
