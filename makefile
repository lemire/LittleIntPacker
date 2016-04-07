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

OBJECTS= bitpacking.o util.o

all: $(OBJECTS) unit

unit : ./tests/unit.c  $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o unit ./tests/unit.c -Iinclude  $(OBJECTS)

bitpacking.o: ./src/bitpacking.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/bitpacking.c -Iinclude  

util.o: ./src/util.c $(HEADERS)
	$(CC) $(CFLAGS) -c ./src/util.c -Iinclude  

clean: 
	rm -f $(OBJECTS) unit
