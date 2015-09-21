
.PHONY : clean test

CXXFLAGS = -W -Wall -O3 -std=c++11

test : quartic
	./quartic

quartic : quartic.cc

clean :
	$(RM) *~ quartic
