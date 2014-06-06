APP = dijkstra

TESTDIR = tests_bin

SRCS := $(shell find src/ -name '*.cpp')
SRCDIRS := $(shell find src/ -name '*.cpp' -exec dirname {} \; | uniq)
TESTS := $(patsubst %.cpp,$(TESTDIR)/%.test ,$(SRCS))
DEPS := $(patsubst %.cpp,$(TESTDIR)/%.d ,$(SRCS))

DEBUG = -g -D DEBUG
INCLUDES = -I../include
CFLAGS =-pedantic -Wall $(INCLUDES)
LDFLAGS =
LIBS =
TESTLIBS = -lboost_unit_test_framework
TESTOPTS = --log_level=test_suite # --report_level=short

DEPENDS = -MT $@ -MD -MP -MF $(subst .o,.d,$@)

SHELL = /bin/bash

.PHONY: all doc run-tests test clean distclean

all: clean buildrepo test

test: $(TESTS)
	@$(call run-tests)

$(TESTDIR)/%.test: %.cpp
	$(CXX) $(DEBUG) $(CFLAGS) $(TESTLIBS) $(DEPENDS) $< -o $@

clean:
	$(RM) -r $(TESTDIR)
	$(RM) $(shell find . -name '*~')
	$(RM) $(shell find . -name '.\#*')

buildrepo:
	@$(call make-repo)

define make-repo
for dir in $(SRCDIRS); \
do \
mkdir -p $(TESTDIR)/$$dir; \
done
endef

define run-tests
for test in $(shell find $(TESTDIR) -name '*.test'); \
do \
./$${test} $(TESTOPTS); \
done
endef


ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif
