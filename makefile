# minimalist makefile
.SUFFIXES:
#
.SUFFIXES: .cpp .o .c .h
ifeq ($(DEBUG),1)
CFLAGS = -fPIC  -std=c99 -ggdb -msse4.1 -march=native -Wall -Wextra -pedantic -Wshadow -fsanitize=undefined  -fno-omit-frame-pointer -fsanitize=address
else
CFLAGS = -fPIC -std=c99 -O3 -msse4.1  -march=native -Wall -Wextra -pedantic -Wshadow
endif # debug

HEADERS=include/bitpacking.h  include/portability.h include/util.h

OBJECTS= bmipacking32.o bitpacking32.o util.o turbobitpacking32.o

all: $(OBJECTS) unit bitpackingbenchmark

unit : ./tests/unit.c  $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o unit ./tests/unit.c -Iinclude  $(OBJECTS)


bitpackingbenchmark : ./benchmarks/bitpackingbenchmark.c  $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o bitpackingbenchmark ./benchmarks/bitpackingbenchmark.c -Iinclude  $(OBJECTS)

bmipacking32.o: ./src/bmipacking32.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/bmipacking32.c -Iinclude


turbobitpacking32.o: ./src/turbobitpacking32.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/turbobitpacking32.c -Iinclude


bitpacking32.o: ./src/bitpacking32.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/bitpacking32.c -Iinclude

util.o: ./src/util.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/util.c -Iinclude

clean:
	rm -f $(OBJECTS) unit bitpackingbenchmark
