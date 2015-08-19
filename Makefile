CC            := g++
LD            := g++
MKDIR         := mkdir -p
CP            := cp

INCDIR := include
SRCDIR := src
BINDIR := bin
TESTDIR:= test
TARGET := ecdhe

CFLAGS        := -Wall -Wextra -std=c++11 -I$(INCDIR)
LDFLAGS       := -lgmp -lgmpxx
DEBUG_FLAGS   := -O0 -g 
RELEASE_FLAGS := -DNDEBUG -O3 -D_FORTIFY_SOURCE=2

.PHONY: all
.PHONY: debug
.PHONY: release
.PHONY: test

include $(SRCDIR)/Makefile

all: $(INCDIR) $(BINDIR) debug

debug: EX_FLAGS = $(DEBUG_FLAGS)
debug: $(BINDIR)/$(TARGET)

release: EX_FLAGS = $(RELEASE_FLAGS)
release: $(BINDIR)/$(TARGET)

test: $(TESTDIR)/*.cpp $(SRCDIR)/ecc.cpp $(SRCDIR)/fp.cpp
	$(CC) -o $(TESTDIR)/ut $(DEBUG_FLAGS) $(CFLAGS) $(LDFLAGS) -I$(TESTDIR) $^
	$(TESTDIR)/ut

$(BINDIR)/$(TARGET): $(foreach O,$(OBJS),$(BINDIR)/$O)
	$(LD) $(LDFLAGS) -o "$@" $^

$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/*.h
	$(CC) $(CFLAGS) $(EX_FLAGS) -c -o "$@" "$<"

$(BINDIR): 
	$(MKDIR) $@
