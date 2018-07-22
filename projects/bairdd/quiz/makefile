test: testme.c
	gcc -o testme -g testme.c -coverage -fpic -lm  $(CFLAGS)
	-testme > test.out
	gcov testme.c >> test.out