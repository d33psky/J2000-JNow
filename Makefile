#

all: testlibNOVA testNOVAS testSOFA comparelibNOVA-NOVAS-SOFA

testlibNOVA: testlibNOVA.c
	gcc testlibNOVA.c -o testlibNOVA -lnova -lm

testNOVAS: testNOVAS.c
	gcc testNOVAS.c novas.c novascon.c nutation.c solsys3.c readeph0.c -o testNOVAS -lm

testSOFA: testSOFA.c
	gcc testSOFA.c -o testSOFA -lsofa_c -lm

comparelibNOVA-NOVAS-SOFA: comparelibNOVA-NOVAS-SOFA.c
	gcc comparelibNOVA-NOVAS-SOFA.c novas.c novascon.c nutation.c solsys3.c readeph0.c -o comparelibNOVA-NOVAS-SOFA -lnova -lsofa_c -lm

clean:
	rm -f testlibNOVA testNOVAS testSOFA comparelibNOVA-NOVAS-SOFA

test: all
	./testlibNOVA
	./testNOVAS
	./testSOFA
	./comparelibNOVA-NOVAS-SOFA

