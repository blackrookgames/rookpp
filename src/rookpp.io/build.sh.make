CC = g++
CFLAGS = -Wall -Wno-unknown-pragmas -g

SRCDIR = /home/zac21/BlackRookGames/cpp/rookpp/src/rookpp.io
SRCSOURCEDIR = $(SRCDIR)/source
SRCHEADERDIR = $(SRCDIR)/header
SRCINCLUDEDIR = $(SRCDIR)/include
SRCOBJECTDIR = $(SRCDIR)/object

MASTERDIR = /home/zac21/BlackRookGames/cpp/rookpp
MASTERBINDIR = $(MASTERDIR)/bin

BINDIR = $(MASTERBINDIR)/rookpp.io
BINPATH = $(BINDIR)/rookpp.io.dll

SRCDEPSFILE = $(SRCDIR)/deps.txt
BINDEPSFILE = $(BINDIR)/rookpp.io.deps.txt
DEPENDENCYARGS = -L $(MASTERBINDIR) -l rookpp/rookpp

SRCSOURCEPATHS = \
$(SRCSOURCEDIR)/rookpp.io.BinReader.cpp \
$(SRCSOURCEDIR)/rookpp.io.BinReader.-methods.cpp \
$(SRCSOURCEDIR)/rookpp.io.BinWriter.cpp \
$(SRCSOURCEDIR)/rookpp.io.BinWriter.-methods.cpp
SRCHEADERPATHS = \
$(SRCHEADERDIR)/rookpp.io.BinReader.h \
$(SRCHEADERDIR)/rookpp.io.BinWriter.h
SRCINCLUDEPATHS = \
$(SRCINCLUDEDIR)/rookpp.BitData.h \
$(SRCINCLUDEDIR)/rookpp.Parsing.h
SRCOBJECTPATHS = \
$(SRCOBJECTDIR)/rookpp.io.BinReader.o \
$(SRCOBJECTDIR)/rookpp.io.BinReader.-methods.o \
$(SRCOBJECTDIR)/rookpp.io.BinWriter.o \
$(SRCOBJECTDIR)/rookpp.io.BinWriter.-methods.o

BINHEADERPATHS = \
$(BINDIR)/rookpp.io.BinReader.h \
$(BINDIR)/rookpp.io.BinWriter.h

$(BINPATH): /home/zac21/BlackRookGames/cpp/rookpp/bin/rookpp.io/rookpp.io.deps.txt $(BINHEADERPATHS) $(SRCOBJECTPATHS)
	@echo -e "\t$(BINPATH)"
	@$(CC) $(CFLAGS) -fpic -shared $(SRCOBJECTPATHS) -o $(BINPATH) $(DEPENDENCYARGS)

$(BINDEPSFILE): $(SRCDEPSFILE)
	@echo -e "\t$(BINDEPSFILE)"
	@cp -u $(SRCDEPSFILE) $(BINDEPSFILE)

$(BINDIR)/rookpp.io.BinReader.h: $(SRCHEADERDIR)/rookpp.io.BinReader.h
	@echo -e "\t$(BINDIR)/rookpp.io.BinReader.h"
	@cp -u $(SRCHEADERDIR)/rookpp.io.BinReader.h $(BINDIR)/rookpp.io.BinReader.h

$(BINDIR)/rookpp.io.BinWriter.h: $(SRCHEADERDIR)/rookpp.io.BinWriter.h
	@echo -e "\t$(BINDIR)/rookpp.io.BinWriter.h"
	@cp -u $(SRCHEADERDIR)/rookpp.io.BinWriter.h $(BINDIR)/rookpp.io.BinWriter.h

$(SRCOBJECTDIR)/rookpp.io.BinReader.o: $(SRCSOURCEDIR)/rookpp.io.BinReader.cpp
	@echo -e "\t$(SRCOBJECTDIR)/rookpp.io.BinReader.o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCHEADERDIR) -I $(SRCINCLUDEDIR) $(DEPENDENCYARGS)

$(SRCOBJECTDIR)/rookpp.io.BinReader.-methods.o: $(SRCSOURCEDIR)/rookpp.io.BinReader.-methods.cpp
	@echo -e "\t$(SRCOBJECTDIR)/rookpp.io.BinReader.-methods.o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCHEADERDIR) -I $(SRCINCLUDEDIR) $(DEPENDENCYARGS)

$(SRCOBJECTDIR)/rookpp.io.BinWriter.o: $(SRCSOURCEDIR)/rookpp.io.BinWriter.cpp
	@echo -e "\t$(SRCOBJECTDIR)/rookpp.io.BinWriter.o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCHEADERDIR) -I $(SRCINCLUDEDIR) $(DEPENDENCYARGS)

$(SRCOBJECTDIR)/rookpp.io.BinWriter.-methods.o: $(SRCSOURCEDIR)/rookpp.io.BinWriter.-methods.cpp
	@echo -e "\t$(SRCOBJECTDIR)/rookpp.io.BinWriter.-methods.o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCHEADERDIR) -I $(SRCINCLUDEDIR) $(DEPENDENCYARGS)

clean:
	@echo Clean
	@rm -fr $(SRCOBJECTDIR)
	@rm -fr $(BINDIR)/*

cleanlibs:
	@echo Clean included libraries
	@rm -fr $(SRCINCLUDEDIR)/*

