# makefile written by lichenbo (111250075)
CC = gcc
CFLAGS = -Wall -g

ODIR=bin
SDIR=src
_OBJS = main.o mypstree.o
_DEPS = mypstree.h
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))
DEPS = $(patsubst %,$(SDIR)/%,$(_DEPS))
OUT=$(ODIR)/main

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)
test: test/test
test/test: test/check_mypstree.c $(DEPS) $(SDIR)/mypstree.c
	$(CC) $< $(SDIR)/mypstree.c -o $@ -lcheck

.PHONY: clean

clean:
	rm $(OBJS) $(OUT)

run:
	bin/main

runtest:
	test/test