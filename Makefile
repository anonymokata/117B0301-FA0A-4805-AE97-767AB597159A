.PHONY: all test clean

all: test infixtorpn

clean:
	$(MAKE) -C test clean
	rm -f *.o
	rm -f infixtorpn

test:
	$(MAKE) -C test full

infixtorpn: librpn.o main.o
	$(CC) -o $@ $^
