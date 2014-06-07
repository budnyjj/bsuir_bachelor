APP = main

OBJDIR = obj
BINDIR = bin

SRCS := $(shell find src/ -name '*.cpp')
SRCDIRS := $(shell find src/ -name '*.cpp' -exec dirname {} \; | uniq)
OBJS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst %.cpp,$(OBJDIR)/%.d,$(SRCS))

DEBUG = -g -D DEBUG
INCLUDES = -I./include
CFLAGS =-pedantic -Wall $(INCLUDES) -c
LDFLAGS =
LIBS =

DEPENDS = -MT $@ -MD -MP -MF $(subst .o,.d,$@)

SHELL = /bin/bash

.PHONY: all doc run-tests test clean distclean

all: buildrepo $(APP)

$(APP): $(OBJS)
	$(CXX) $(DEBUG) $(LDFLAGS) $^ $(LIBS) -o $(addprefix $(BINDIR)/, $@)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(DEBUG) $(CFLAGS) $(DEPENDS) $< -o $@

clean:
	$(RM) -r $(OBJDIR)
	$(RM) $(shell find . -name '*~')
	$(RM) $(shell find . -name '.\#*')

distclean: clean
	$(RM) $(APP)

buildrepo:
	@$(call make-repo)

define make-repo
for dir in $(SRCDIRS); \
do \
mkdir -p $(OBJDIR)/$$dir; \
done
endef

ifneq "$(MAKECMDGOALS)" "distclean"
ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif
endif

run:
	./$(BINDIR)/$(APP) ./tests/samples/graph.in 1

run-tests:
	$(MAKE) -C tests

doc:
	doxygen Doxyfile
