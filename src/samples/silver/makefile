
CC=g++
# Flags
# quickfix asks for -fexceptions -finline-functions -lquickfix -lpthreads -lxml2 -lz
CFLAGS=-c -Wall -std=c++11 -I ../../dependancies/quickfix/include/ -fexceptions -finline-functions
#LDFLAGS=-lquickfix -lpthreads -lxml2 -lz
LDFLAGS=-lquickfix -lpthread -lxml2 -lz -L ../../../lib
SOURCES=main.cpp InboundFIXSession.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../../../bin/silver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)

