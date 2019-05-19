CXX           = g++
CPPFLAGS      = -O4 -Wall -I. -I../include/
DEST          = /usr/local/bin
LDFLAGS       = -L./
LIBS          = 
OBJS          = bitmap24.o bitmap24_filter.o main.o
PROGRAM       = ../bin/main

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	${CXX} $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

clean:
	rm -f *.o *~ $(PROGRAM)

