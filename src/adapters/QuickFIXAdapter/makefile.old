
CC=g++
# Flags
# quickfix asks for -fexceptions -finline-functions -lquickfix -lpthreads -lxml2 -lz
# -I ../../dependancies/quickfix/include/ -fexceptions -finline-functions
CFLAGS=-Wall -c -std=c++11 -fPIC -I ../../dependancies/quickfix/include/
LDFLAGS=-lpthread -lxml2 -lz -L ../../lib
SOURCES=QuickFIXAdapter.cpp QuickFIXMessageMapper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=../../../lib/libAdapterQuickFIX.so

all:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) -shared -o $(LIBRARY) $(OBJECTS)

clean:
	rm -rf $(OBJECTS) $(LIBRARY)

