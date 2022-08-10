CC=gcc
AR=ar

all: conio.o libconio.a testconio

conio.o:
	${CC} -c conio.c -o conio.o
	
libconio.a:
	${AR} -rcs libconio.a conio.o
	
testconio:
	${CC} -I ${PWD} -c testconio.c -o testconio.o	
	${CC} testconio.o -o testconio -L ${PWD} -lconio
	
clean:
	rm -Rfv *.a *.o testconio
