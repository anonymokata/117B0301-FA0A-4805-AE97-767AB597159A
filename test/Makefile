CFLAGS = `pkg-config --cflags check`
LIBS = `pkg-config --libs check`
VPATH=..

TEST_OBJECTS = test_librpn.o

all: test_librpn
	./test_librpn

full: all memtest

test_librpn: librpn.o $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: test_librpn
	CK_FORK=no valgrind --leak-check=full ./test_librpn

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f test_librpn
