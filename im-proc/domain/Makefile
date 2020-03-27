ROOT = ../bcl

CFLAGS = -Wall -Wextra -Werror -std=c99 -I$(ROOT)/include
LDFLAGS = -L$(ROOT)/lib
LDLIBS = -lbcl -lm

MOVE = ./move
SCROLL = ./scroll
FLIP = ./flip
SHEAR = ./shear

LENA = ../data/lena-color.ppm

OBJ = domain.o
BIN = \
	move\
	flip\
	shear\
	scroll


all: $(BIN)

clean:
	$(RM) $(OBJ) $(BIN) *.ppm

test: $(BIN)
	$(MOVE) 0 30 $(LENA) move0_30.ppm
	$(MOVE) 30 0 $(LENA) move30_0.ppm
	$(MOVE) 30 30 $(LENA) move30_30.ppm
	$(MOVE) -30 -30 $(LENA) move-30_-30.ppm
	$(SCROLL) 0 30 $(LENA) scroll0_30.ppm
	$(SCROLL) 30 0 $(LENA) scroll30_0.ppm
	$(SCROLL) 30 30 $(LENA) scroll30_30.ppm
	$(SCROLL) -30 -30 $(LENA) scroll-30_-30.ppm
	$(FLIP) h $(LENA) flip_h.ppm
	$(FLIP) v $(LENA) flip_v.ppm
	$(FLIP) vh $(LENA) flip_vh.ppm
	$(FLIP) hh $(LENA) flip_hh.ppm
	$(FLIP) t $(LENA) flip_t.ppm
	$(FLIP) ht $(LENA) flip_ht.ppm
	$(SHEAR) h 30 $(LENA) shear_h_30.ppm
	$(SHEAR) h -30 $(LENA) shear_h_-30.ppm
	$(SHEAR) v 30 $(LENA) shear_v_30.ppm
	$(SHEAR) v -30 $(LENA) shear_v_-30.ppm


.PHONY: all clean test
