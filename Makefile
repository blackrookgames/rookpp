ifneq ($(notdir $(CURDIR)),bin)

export DIR := $(CURDIR)
export SRCDIR := $(DIR)/src
export OBJDIR := $(DIR)/obj
export BINDIR := $(DIR)/bin

export SRCHDRDIR := $(SRCDIR)/hdr
export SRCDEPDIR := $(SRCDIR)/dep
export SRCSRCDIR := $(SRCDIR)/src

LIBS := $(foreach fname,$(notdir $(wildcard $(SRCHDRDIR)/*.h)),$(fname:.h=))

all:
	@mkdir -p $(BINDIR)
	@libs=($(LIBS)); \
	for lib in "$${libs[@]}"; do \
		$(MAKE) --no-print-directory -C $(BINDIR) -f $(DIR)/Makefile $$lib; \
	done

clean:
	@echo Clean
	@rm -fr $(BINDIR) $(OBJDIR)

else

LIB := $(MAKECMDGOALS)
LIB_BPATH := $(BINDIR)/$(LIB).a #TODO: Consider Windows
#hdr
LIB_HDRSPATH := $(SRCHDRDIR)/$(LIB).h
LIB_HDRBPATH := $(BINDIR)/$(LIB).h
#dep
LIB_DEPSPATH := $(SRCDEPDIR)/$(LIB).dep
LIB_DEPBPATH := $(BINDIR)/$(LIB).dep
#src
LIB_SRCSDIR := $(SRCSRCDIR)/$(LIB)
LIB_SRCSPATHS := $(shell \
	for path in $$(find $(LIB_SRCSDIR) -type f -name *.cpp); do \
		echo -n "$${path} "; \
	done )
LIB_SRCRPATHS := $(foreach path,$(LIB_SRCSPATHS),$(shell realpath --relative-to $(SRCSRCDIR) $(path)))
LIB_SRCOPATHS := $(foreach path,$(LIB_SRCRPATHS),$(OBJDIR)/$(path:.cpp=.o))

$(LIB): $(LIB_BPATH);

$(LIB_BPATH): $(LIB_HDRBPATH) $(LIB_DEPBPATH) $(LIB_SRCOPATHS)
	@echo $(notdir $@)
	@mkdir -p $(shell dirname $@)
	@ar rcs $(LIB_BPATH) $(LIB_SRCOPATHS) #TODO: Consider Windows

$(LIB_HDRBPATH): $(LIB_HDRSPATH)
	@echo $(notdir $@)
	@mkdir -p $(shell dirname $@)
	@cp $< $@

$(LIB_DEPBPATH): $(LIB_DEPSPATH)
	@echo $(notdir $@)
	@mkdir -p $(shell dirname $@)
	@if [ -f $< ]; then \
		cp "$<" "$@"; \
	else \
		rm -fr "$@" ; \
		echo "#$(LIB) does not contain any dependencies" >>"$@" ; \
	fi

$(LIB_DEPSPATH): ;

$(OBJDIR)/%.o: $(SRCSRCDIR)/%.cpp
	@echo $(notdir $@)
	@mkdir -p $(shell dirname $@)
	@g++ -c -g -o $@ $< -I$(BINDIR)

endif