CC = g++
CFLAGS = -Wall -Wno-unknown-pragmas -g

SRCDIR = /home/zac21/BlackRookGames/cpp/rookpp/src/rookpp
SRCSOURCEDIR = $(SRCDIR)/source
SRCHEADERDIR = $(SRCDIR)/header
SRCINCLUDEDIR = $(SRCDIR)/include
SRCOBJECTDIR = $(SRCDIR)/object

MASTERDIR = /home/zac21/BlackRookGames/cpp/rookpp
MASTERBINDIR = $(MASTERDIR)/bin

BINDIR = $(MASTERBINDIR)/rookpp
BINPATH = $(BINDIR)/rookpp.dll

SRCDEPSFILE = $(SRCDIR)/deps.txt
BINDEPSFILE = $(BINDIR)/rookpp.deps.txt

SRCSOURCEPATHS = \
$(SRCSOURCEDIR)/rookpp.BitData.cpp \
$(SRCSOURCEDIR)/rookpp.Parsing.cpp
SRCHEADERPATHS = \
$(SRCHEADERDIR)/rookpp.BitData.h \
$(SRCHEADERDIR)/rookpp.Parsing.h
SRCINCLUDEPATHS =
SRCOBJECTPATHS = \
$(SRCOBJECTDIR)/rookpp.BitData.o \
$(SRCOBJECTDIR)/rookpp.Parsing.o

BINHEADERPATHS = \
$(BINDIR)/rookpp.BitData.h \
$(BINDIR)/rookpp.Parsing.h

$(BINPATH): /home/zac21/BlackRookGames/cpp/rookpp/bin/rookpp/rookpp.deps.txt $(BINHEADERPATHS) $(SRCOBJECTPATHS)
	@echo -e "\t$(BINPATH)"
	@$(CC) $(CFLAGS) -fpic -shared $(SRCOBJECTPATHS) -o $(BINPATH) $(DEPENDENCYARGS)

$(BINDEPSFILE): $(SRCDEPSFILE)
	@echo -e "\t$(BINDEPSFILE)"
	@cp -u $(SRCDEPSFILE) $(BINDEPSFILE)

$(BINDIR)/rookpp.BitData.h: $(SRCHEADERDIR)/rookpp.BitData.h
	@echo -e "\t$(BINDIR)/rookpp.BitData.h"
	@cp -u $(SRCHEADERDIR)/rookpp.BitData.h $(BINDIR)/rookpp.BitData.h

$(BINDIR)/rookpp.Parsing.h: $(SRCHEADERDIR)/rookpp.Parsing.h
	@echo -e "\t$(BINDIR)/rookpp.Parsing.h"
	@cp -u $(SRCHEADERDIR)/rookpp.Parsing.h $(BINDIR)/rookpp.Parsing.h

$(SRCOBJECTDIR)/rookpp.BitData.o: $(SRCSOURCEDIR)/rookpp.BitData.cpp
	@echo -e "\t$(SRCOBJECTDIR)/rookpp.BitData.o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCHEADERDIR) -I $(SRCINCLUDEDIR) $(DEPENDENCYARGS)

$(SRCOBJECTDIR)/rookpp.Parsing.o: $(SRCSOURCEDIR)/rookpp.Parsing.cpp
	@echo -e "\t$(SRCOBJECTDIR)/rookpp.Parsing.o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCHEADERDIR) -I $(SRCINCLUDEDIR) $(DEPENDENCYARGS)

clean:
	@echo Clean
	@rm -fr $(SRCOBJECTDIR)
	@rm -fr $(BINDIR)/*

cleanlibs:
	@echo Clean included libraries
	@rm -fr $(SRCINCLUDEDIR)/*

