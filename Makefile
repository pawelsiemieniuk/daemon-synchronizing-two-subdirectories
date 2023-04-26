.PHONY: build

CC=gcc

FILENAME=daemon
BINDIR=bin/
DIRS=. ./lib
FLAGS= -pthread

CFILES=$(foreach D,$(DIRS),$(wildcard $(D)/*.c))


build: $(FILENAME)
$(FILENAME): $(CFILES)
	$(CC) $(FLAGS) -o $(BINDIR)$@ $^ 
