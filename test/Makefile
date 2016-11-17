CFLAGS = `pkg-config --cflags check` -g --std=c99
LIBS = `pkg-config --libs check`
VPATH=..

TEST_OBJECTS = test_librpn.o test_stack.o test_sstack.o
APPLICATION_OBJECTS = librpn.o stack.o stringstack.o aststack.o ast.o 

all: test_librpn
	./test_librpn

full: all memtest

test_librpn: ${APPLICATION_OBJECTS} $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: test_librpn
	CK_FORK=no valgrind --leak-check=full ./test_librpn

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f test_librpn
