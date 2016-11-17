.PHONY: all test clean

CFLAGS = -g -std=c99

all: test infixtorpn

clean:
	$(MAKE) -C test clean
	rm -f *.o
	rm -f infixtorpn

test:
	$(MAKE) -C test full

infixtorpn: librpn.o stack.o stringstack.o aststack.o ast.o main.o
	$(CC) -o $@ $^
