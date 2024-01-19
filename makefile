all: encoder

encoder: encoder.o
	gcc Wall -g encoder.o -o encoder

encoder.o: encoder.c
	gcc Wall -g -c encoder.c

.PHONY: clean

clean:
	rm *.o encoder
