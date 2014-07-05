all: heisenberg

skynet: skynet.cc
	g++ -Wall -ftemplate-depth-2000000 -ftemplate-backtrace-limit=0 -o $@ $@.cc

heisenberg: heisenberg.cc
	g++ -O3 -Wall -o $@ $<

clean: 
	rm -f skynet skynet2 heisenberg
