
compile:
	cc -save-temps -o out test.c
	cat out-test.i

clear:
	rm -f out*
