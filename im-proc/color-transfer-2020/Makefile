ROOT=../bcl

CPPFLAGS = -I$(ROOT)/include
CFLAGS   = -Wall -Wextra -Werror -pedantic -std=c99
LDFLAGS  = -L$(ROOT)/lib
LDLIBS   = -lbcl -lm

CT = ./color-transfer
OCEAN = ./data/ocean.ppm
FOREST = ./data/forest.ppm
FLOWER = ./data/flower.ppm
MOUNTAIN = ./data/mountain.ppm

BIN=\
	color-transfer

.PHONY: all
all:$(BIN)

.PHONY: clean cleanall test

test:$(BIN)
	$(CT) $(OCEAN) $(FOREST) a.ppm
	$(CT) $(FLOWER) $(MOUNTAIN) b.ppm


clean:
	$(RM) *.o *~ *.ppm color-transfer
cleanall: clean
	$(RM) $(BIN)