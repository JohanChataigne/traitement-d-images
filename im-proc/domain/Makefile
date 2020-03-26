ROOT = ../bcl

CFLAGS = -Wall -Wextra -Werror -std=c99 -I$(ROOT)/include 
LDFLAGS = -L$(ROOT)/lib 
LDLIBS = -lbcl

OBJ = domain.o
BIN = \
	move\
<<<<<<< HEAD
	shear
=======
	shear\
	scroll
>>>>>>> c7ba4240653416de66f6c51e10120c1a899db38d

all: $(BIN)

shear: $(OBJ)

clean:
	$(RM) $(OBJ) $(BIN) *.ppm

.PHONY: all clean 
