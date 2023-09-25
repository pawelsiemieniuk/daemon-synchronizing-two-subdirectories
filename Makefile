.PHONY: build

CC=gcc

FILENAME=sync2d
BINDIR=bin/
DIRS=. ./lib
FLAGS= -pthread

CFILES=$(foreach D,$(DIRS),$(wildcard $(D)/*.c))


build: $(FILENAME)
$(FILENAME): $(CFILES)
	$(CC) $(FLAGS) -o $(BINDIR)$@ $^ 
