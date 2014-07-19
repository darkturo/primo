ifndef _ARCH
   _ARCH := __$(shell uname)__
   export _ARCH
endif 

all: heisenberg sundaram meteoro 

skynet: skynet.cc
	g++ -Wall -ftemplate-depth-2000000 -ftemplate-backtrace-limit=0 -o $@ $@.cc

heisenberg: heisenberg.cc
	g++ -m64 -D$(_ARCH) -O3 -Wall -o $@ $<

sundaram: sundaram.cc
	g++ -m64 -D$(_ARCH) -O3 -Wall -o $@ $< 

meteoro: meteoro.cc 
	g++ -o format.o -c cppformat/format.cc 
	g++ -std=c++11 -m64 -D$(_ARCH) -O3 -ftree-vectorize -msse2 -Wall -o $@ $< format.o

benchmark:
	nice -20 perl -MBenchmark -e 'timethese(20, {heisenberg => q(system("./heisenberg")), \
																sundaram => q(system("./sundaram")), \
																meteoro => q(system("./meteoro"))})'

clean: 
	rm -f skynet skynet2 heisenberg meteoro sundaram
