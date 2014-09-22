
CC=g++
# Flags
CFLAGS=-c -Wall -std=c++11 -I ../../dependancies/quickfix/include/ -I ../../adapters/ -I ../../dependancies/fixprotobuf/cpp_out/ -fexceptions -finline-functions 
#LDFLAGS=-lquickfix -lpthreads -lxml2 -lz
LDFLAGS=-Wl,--no-as-needed -lAdapterQuickFIX -lmetal -lquickfix -lfixprotobuf -lprotobuf -lpthread -lxml2 -lz -L ../../../lib
SOURCES=main.cpp InboundFIXSession.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../../../bin/silver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

