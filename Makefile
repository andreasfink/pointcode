##
# File: Makefile
# Project "pointcode"
# (c) 2005 Andreas Fink
# Create: Andreas Fink (andreas@fink.org)
#

EXEDIR=/usr/local/bin
CFLAGS=-O2
CC=gcc
LIBS= 


all: pc pc644

install: pc644 pc
	-mkdir -p -m 755 $(DESTDIR)/usr/local/bin
	-install -b -g bin -o root -m 755 pc $(DESTDIR)${EXEDIR}/pc
	-install -b -g bin -o root -m 755 pc644 $(DESTDIR)${EXEDIR}/pc644
	
clean:
	-rm -f *.o

pc.o:	pc.c
	gcc      -c -o pc.o pc.c
	
pc:	pc.o
	gcc    -o pc pc.o 


pc644.o:	pc.c
	gcc   -DUSE644=1 -c -o pc644.o pc.c
	
pc644:	pc644.o
	gcc    -o pc644 pc644.o 

.o:	.c

