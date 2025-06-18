#Get OS specific info
OS_CMD := 
#Is this Windows?
ifeq ($(OS),Windows_NT)
ifeq ($(strip $(UNIX)),)
$(error Please set UNIX in your environment)
endif
OS_CMD := $(UNIX)/
#If not, assume this is linux
else
OS_CMD :=
endif

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
	@$(OS_CMD)mkdir -p $(BINDIR)
	@libs=($(LIBS)); \
	for lib in "$${libs[@]}"; do \
		$(MAKE) --no-print-directory -C $(BINDIR) -f $(DIR)/Makefile $$lib; \
	done

clean:
	@$(OS_CMD)echo Clean
	@$(OS_CMD)rm -fr $(BINDIR) $(OBJDIR)

else

LIB := $(MAKECMDGOALS)
LIB_BPATH := $(BINDIR)/$(LIB).a
#hdr
LIB_HDRSPATH := $(SRCHDRDIR)/$(LIB).h
LIB_HDRBPATH := $(BINDIR)/$(LIB).h
#dep
LIB_DEPSPATH := $(SRCDEPDIR)/$(LIB).dep
LIB_DEPBPATH := $(BINDIR)/$(LIB).dep
#src
LIB_SRCSDIR := $(SRCSRCDIR)/$(LIB)
LIB_SRCSPATHS := $(shell \
	for path in $$($(OS_CMD)find $(LIB_SRCSDIR) -type f -name *.cpp); do \
		$(OS_CMD)echo -n "$${path} "; \
	done )
LIB_SRCRPATHS := $(foreach path,$(LIB_SRCSPATHS),$(shell $(OS_CMD)realpath --relative-to $(SRCSRCDIR) $(path)))
LIB_SRCOPATHS := $(foreach path,$(LIB_SRCRPATHS),$(OBJDIR)/$(path:.cpp=.o))

$(LIB): $(LIB_BPATH);

$(LIB_BPATH): $(LIB_HDRBPATH) $(LIB_DEPBPATH) $(LIB_SRCOPATHS)
	@$(OS_CMD)echo $(notdir $@)
	@$(OS_CMD)mkdir -p $(shell $(OS_CMD)dirname $@)
	@$(OS_CMD)ar rcs $(LIB_BPATH) $(LIB_SRCOPATHS)

$(LIB_HDRBPATH): $(LIB_HDRSPATH)
	@$(OS_CMD)echo $(notdir $@)
	@$(OS_CMD)mkdir -p $(shell $(OS_CMD)dirname $@)
	@$(OS_CMD)cp $< $@

$(LIB_DEPBPATH): $(LIB_DEPSPATH)
	@$(OS_CMD)echo $(notdir $@)
	@$(OS_CMD)mkdir -p $(shell $(OS_CMD)dirname $@)
	@if [ -f $< ]; then \
		$(OS_CMD)cp "$<" "$@"; \
	else \
		$(OS_CMD)rm -fr "$@" ; \
		$(OS_CMD)echo "#$(LIB) does not contain any dependencies" >>"$@" ; \
	fi

$(LIB_DEPSPATH): ;

$(OBJDIR)/%.o: $(SRCSRCDIR)/%.cpp
	@$(OS_CMD)echo $(notdir $@)
	@$(OS_CMD)mkdir -p $(shell dirname $@)
	@$(OS_CMD)g++ -c -g -o $@ $< -I$(BINDIR)

endif