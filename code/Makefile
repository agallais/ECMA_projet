SYSTEM     = x86-64_sles10_4.1
LIBFORMAT  = static_pic

#------------------------------------------------------------
#
# When you adapt this makefile to compile your CPLEX programs
# please copy this makefile and set CPLEXDIR and CONCERTDIR to
# the directories where CPLEX and CONCERT are installed.
#
#------------------------------------------------------------

CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio125/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio125/concert

# ---------------------------------------------------------------------
# Compiler selection
# ---------------------------------------------------------------------


CXX = g++

# ---------------------------------------------------------------------
# Compiler options
# ---------------------------------------------------------------------

CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD

# ---------------------------------------------------------------------
# Link options and libraries
# ---------------------------------------------------------------------
CXX = g++
CXXFLAGS = -g -Wall -O
CXXFLAGS += -I$(CPLEX_DIR)/include

LINK.o = $(LINK.cc)
LDFLAGS += -L$(CPLEX_DIR)/lib/x86-64_linux/static_pic
LDLIBS += -lcplex -lm -pthread

all: main

main.o: configuration.h solution.h

configuration.o : solution.h


clean:  $(RM) *~ *.o main

.PHONY: all clean
