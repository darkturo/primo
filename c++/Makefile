ifndef _ARCH
   _ARCH := __$(shell uname)__
   export _ARCH
endif 

all: heisenberg sundaram

skynet: skynet.cc
	g++ -Wall -ftemplate-depth-2000000 -ftemplate-backtrace-limit=0 -o $@ $@.cc

heisenberg: heisenberg.cc
	g++ -m64 -D$(_ARCH) -O3 -Wall -o $@ $<

sundaram: sundaram.cc
	g++ -m64 -D$(_ARCH) -O3 -Wall -o $@ $< 

clean: 
	rm -f skynet skynet2 heisenberg
