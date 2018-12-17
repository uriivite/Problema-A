CC=g++
CFLAGS=-Wall -g
jaccard: jaccard.cc
	$(CC) $(CFLAGS) -o jaccard jaccard.cc

signatures:	signatures.cc
	$(CC) $(CFLAGS) -o signatures signatures.cc

LHS: LHS.cc
	$(CC) $(CFLAGS) -o LHS LHS.cc

.PHONY:clean
clean:
	rm -rf *.o
