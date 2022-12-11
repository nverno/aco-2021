ROOTDIR = $(CURDIR)/..
-include config.mk

CC = g++
CPPINCLUDE = -I${ROOTDIR}/lib
CXXFLAGS += -Wall -Wshadow -fsanitize=undefined -O2 -g -std=c++17 ${CPPINCLUDE}

LSRC = $(ROOTDIR)/lib/aoc.cpp
CSRC = $(wildcard *.cpp)
OBJS = ${CSRC:.cpp=.o}
LIB = aoc.o

INPUT ?= $(CURDIR)/input
DAYS = $(wildcard *.cpp)

RUN = ./$(1) < $(INPUT)/day$(2).txt
BUILD = $(CC) ${CXXFLAGS} -o $(1) $(2) ${SRC}

ADVENT = https://adventofcode.com
SESSION := $(shell cat $(CURDIR)/session)
CURL = curl -H "Cookie: session=$(SESSION)"
export

all:
	@echo $(YEAR): $(OBJS)

%.out: %.o ${LIB}
	$(CC) ${CXXFLAGS} ${LIB} $< -o $@

%.o: %.cpp ${LIB}
	$(CC) -c $< ${CXXFLAGS}

in%: $(INPUT)/day%.txt
	@make $(INPUT)/day$*.txt

$(INPUT)/day%.txt:
	$(CURL) -Lo $@ $(ADVENT)/$(YEAR)/day/$*/input

submit%-1:
	$(CURL) -F answer=$(ANSWER1) -F level=1 $(ADVENT)/$(YEAR)/day/$*/answer

day%: day%.cpp ${LIB}
	@make day$*.o day$*.out

r-%-1: day%-1.out
	./$^ < $(INPUT)/day$*.txt

r-%-2: day%-2.out
	./$^ < $(INPUT)/day$*.txt

${LIB}: ${LSRC}
	$(CC) -c $< $(CXXFLAGS)

run-test:
ifdef EXE
	@if [ -f "$(TESTTMP)" ]; then ./$(EXE) < "$(TESTTMP)"; \
	elif [ -f "$(TEST)" ]; then ./$(EXE) < "$(TEST)";      \
	else echo "$(TEST)" not found;                         \
	fi
else
	@echo EXE not defined
endif

t%:
	@make -s TESTTMP=$(INPUT)/tmp.txt d$*

d%:
	@make $(INPUT)/day$*.txt
	@if [ -f "day$*-1.cpp" ]; then                                    \
		make day$*-1 >/dev/null;                                  \
		echo -n "part 1: ";                                       \
		make -s EXE=day$*-1.out TEST=$(INPUT)/day$*.txt run-test; \
	fi
	@if [ -f "day$*-2.cpp" ]; then                                    \
		make day$*-2 >/dev/null;                                  \
		echo -n "part 2: ";                                       \
		make -s EXE=day$*-2.out TEST=$(INPUT)/day$*.txt run-test; \
	fi

clean:
	$(RM) -r core *~ *.o *.out *.exe
