#

all:	testlibNOVA testNOVAS testSOFA

testlibNOVA: testlibNOVA.c
	gcc testlibNOVA.c -o testlibNOVA -lnova -lm

testNOVAS: testNOVAS.c
	gcc testNOVAS.c novas.c novascon.c nutation.c solsys3.c readeph0.c -o testNOVAS -lm

testSOFA: testSOFA.c
	gcc testSOFA.c -o testSOFA -lsofa_c -lm

clean:
	rm -f testlibNOVA testNOVAS testSOFA

test: all
	./testlibNOVA
	./testNOVAS
	./testSOFA

