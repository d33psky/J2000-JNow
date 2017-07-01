#

all: testERFA testlibNOVA testNOVAS testSOFA comparelibNOVA-NOVAS-SOFA-ERFA

testERFA:
	gcc testERFA.c -o testERFA -lerfa -lm

testlibNOVA: testlibNOVA.c
	gcc testlibNOVA.c -o testlibNOVA -lnova -lm

testNOVAS: testNOVAS.c
	gcc testNOVAS.c novas.c novascon.c nutation.c solsys3.c readeph0.c -o testNOVAS -lm

testSOFA: testSOFA.c
	gcc testSOFA.c -o testSOFA -lsofa_c -lm

comparelibNOVA-NOVAS-SOFA-ERFA: comparelibNOVA-NOVAS-SOFA-ERFA.c
	gcc comparelibNOVA-NOVAS-SOFA-ERFA.c novas.c novascon.c nutation.c solsys3.c readeph0.c -o comparelibNOVA-NOVAS-SOFA -lnova -lsofa_c -lerfa -lm

clean:
	rm -f testERFA testlibNOVA testNOVAS testSOFA comparelibNOVA-NOVAS-SOFA-ERFA

test: all
	./testlibNOVA
	./testNOVAS
	./testERFA
	./testSOFA
	./comparelibNOVA-NOVAS-SOFA-ERFA

