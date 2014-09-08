
CC=g++
# Flags
# quickfix asks for -fexceptions -finline-functions -lquickfix -lpthreads -lxml2 -lz
# -I ../../dependancies/quickfix/include/ -fexceptions -finline-functions
CFLAGS=-Wall -std=c++11 -shared -fPIC -I cpp_out/
#LDFLAGS=-lquickfix -lpthreads -lxml2 -lz
LDFLAGS=-lpthread -lxml2 -lz -L ../../lib
# Compile all generated files
SOURCES=$(wildcard ./cpp_out/*.cc)
LIBRARY=../../../lib/libfixprotobuf.so

all:
	$(CC) $(CFLAGS) -o $(LIBRARY) $(SOURCES)

clean:
	rm -rf *o $(LIBRARY)

