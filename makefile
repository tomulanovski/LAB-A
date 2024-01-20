all: encoder

encoder: encoder.o
	gcc -m32 -Wall -g encoder.o -o encoder

encoder.o: encoder.c
	gcc -m32 -Wall -g -c encoder.c

.PHONY: clean

clean:
	rm *.o encoder
