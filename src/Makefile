WFLAG  = -Wall -Werror
ifeq ($(PRINT),1)
	CFLAG  = -DPRINT_EXEC
endif
TARGET = bin
OPT    = -O3
RM     = rm
TAG    = ctags
CC     = g++ -std=c++11 $(OPT) $(WFLAG) $(CFLAG) -I. -pthread

CC_OBJS = main.o
INFRA_OBJS = infra/cube.o infra/state.o infra/node.o infra/problem.o infra/solver.o
#IO_OBJS = io/io.o io/lef.o io/def.o io/rpt.o io/guide.o io/weight.o

OBJS = $(CC_OBJS) $(INFRA_OBJS)

SRCS = ${OBJS:%.o=%.cpp}
BFILE = cube
AFILE = cube.a

define copy_build
	mkdir -p ../$(TARGET)
	mv -u $(BFILE) ../$(TARGET)
endef

.PHONY: all
all: $(BFILE)

.PHONY: install
install: $(BFILE)
	$(call copy_build)

$(BFILE): $(OBJS)
	$(CC) -o $(BFILE) $(OBJS)
	$(call copy_build)

%.o : %.cpp
	$(CC) -o $*.o -c $*.cpp

.PHONY: clean
clean:
	$(RM) -f */*.o *.o
	$(RM) -f $(BFILE) $(AFILE)

.PHONY: cleanAll
cleanAll:
	$(RM) -f */*.o *.o
	$(RM) -f $(BFILE) $(AFILE)
	$(RM) -f ../$(TARGET)/$(BFILE)

.PHONY: runTest
runTest:
	../bin/$(BFILE) -c 3 -o 3 -r 1 -t 1 -f ../bin/results.csv

.PHONY: compileAndTest
compileAndTest:
	echo "\n\tCLEANING\n";
	make cleanAll
	echo "\n\tCOMPILING\n";
	make -j $(PRINT)
	echo "\n\tTESTING\n";
	make runTest