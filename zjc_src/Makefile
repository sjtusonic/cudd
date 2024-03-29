# main: simple combinational logic equivalence checker based
#         on BDD comparison            
#---------------------------------------------------------------------------
.SUFFIXES: .o .c .u

CC	= gcc -std=c99
RANLIB	= ranlib

EXE	=
TARGET	= tutorial$(EXE)
TARGETu = tutorial-u

#WHERE	= /usr/local/cudd-2.4.1
#WHERE	= cudd-2.4.1
WHERE	= /home/zz/Downloads/cudd-3.0.0
# /home/zz/Downloads/cudd-3.0.0/dddmp/dddmp.h

INCLUDE = $(WHERE)/include -I$(WHERE)/dddmp -I$(WHERE)/util -I$(WHERE)/cudd -I$(WHERE)
#INCLUDE = $(WHERE)/dddmp

LIBS	= $(WHERE)/dddmp/.libs/libdddmp.a $(WHERE)/cudd/.libs/libcudd.a \
	\


BLIBS	= -kL$(WHERE)/dddmp -kldddmp -kL$(WHERE)/cudd -klcudd -kL$(WHERE)/mtr \
	-klmtr -kL$(WHERE)/st -klst -kL$(WHERE)/util -klutil

LINTLIBS = $(WHERE)/llib-ldddmp.a $(WHERE)/cudd/llib-lcudd.ln \
	$(WHERE)/mtr/llib-lmtr.ln $(WHERE)/st/llib-lst.ln \
	$(WHERE)/util/llib-lutil.ln

SRC	= tutorial.c
#HDR	= $(WHERE)/include/dddmp.h $(WHERE)/include/cudd.h \
	#$(WHERE)/include/cuddInt.h
HDR	= $(WHERE)/dddmp/dddmp.h $(WHERE)/cudd/cudd.h \
	$(WHERE)/cudd/cuddInt.h

OBJ	= $(SRC:.c=.o)
UBJ	= $(SRC:.c=.u)

MFLAG	=
ICFLAGS = -g -O6 -Wall
XCFLAGS = -DHAVE_IEEE_754 -DBSD
CFLAGS	= $(ICFLAGS) $(MFLAG) $(XCFLAGS)
DDDEBUG =
#DDDEBUG = -DDD_STATS -DDD_VERBOSE -DDD_CACHE_PROFILE -DDD_UNIQUE_PROFILE -DDD_DEBUG

LDFLAGS =
#LDFLAGS = -jmpopt
#LDFLAGS = -non_shared -om -taso

LINTFLAGS = -u -n -DDD_STATS -DDD_CACHE_PROFILE -DDD_VERBOSE -DDD_DEBUG -DDD_UNIQUE_PROFILE

#------------------------------------------------------

$(TARGET): $(SRC) $(OBJ) $(HDR) $(LIBS) $(MNEMLIB)
	$(PURE) $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LIBS) $(MNEMLIB) -lm

.c.o: $(HDR)
	$(CC) -c $< -I$(INCLUDE) $(CFLAGS) $(DDDEBUG)

# if the header files change, recompile
$(OBJ): $(HDR)
$(UBJ): $(HDR)

.c.u: $(SRC) $(HDR)
	cc -j -I$(INCLUDE) $(XCFLAGS) $<

lint: $(SRC) $(HDR) $(LINTLIBS)
	lint $(LINTFLAGS) -I$(INCLUDE) $(SRC) $(LINTLIBS)

tags: $(SRC) $(HDR)
	ctags $(SRC) $(HDR)

all: $(TARGET) $(TARGETu) lint tags

pixie: $(TARGETu)
	pixie $(TARGETu)

clean:
	rm -f *.o *.u mon.out gmon.out *.pixie *.Addrs *.Counts mnem.* \
	.pure core *.warnings tutorial

distclean: clean
	rm -f $(TARGET) $(TARGETu) *.bak *~ .gdb_history *.qv *.qx
