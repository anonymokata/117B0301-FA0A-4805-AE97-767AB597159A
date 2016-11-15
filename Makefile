.PHONY: all test clean

CFLAGS = -g

all: test infixtorpn

clean:
	$(MAKE) -C test clean
	rm -f *.o
	rm -f infixtorpn

test:
	$(MAKE) -C test full

infixtorpn: librpn.o stack.o stringstack.o main.o
	$(CC) -o $@ $^
