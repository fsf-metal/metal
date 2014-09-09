
CC=g++
# Flags
# quickfix asks for -fexceptions -finline-functions -lquickfix -lpthreads -lxml2 -lz
# -I ../../dependancies/quickfix/include/ -fexceptions -finline-functions
CFLAGS=-Wall -c -std=c++11 -fPIC -I ../dependancies/fixprotobuf/cpp_out/
LDFLAGS=-lfixprotobuf -lprotobuf -lpthread -lxml2 -lz -L ../../lib
SOURCES=Adapter.cpp TradingAdapter.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=../../lib/libmetal.so

all:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) -shared -o $(LIBRARY) $(OBJECTS)

clean:
	rm -rf $(OBJECTS) $(LIBRARY)

