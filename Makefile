CC = g++
SRC = ../lib/aoc.cpp
CPPINCLUDE = -I../lib
CXXFLAGS += -Wall -Wshadow -fsanitize=address -fsanitize=undefined -O2 -g -std=c++17
INPUT ?= $(CURDIR)/input

DAYS = $(wildcard *.cpp)

RUN = ./$(1) < $(INPUT)/day$(2).txt
BUILD = $(CC) ${CXXFLAGS} ${CPPINCLUDE} -o $(1) $(2) ${SRC}
export

%.out: %.cpp
	$(CC) ${CXXFLAGS} ${CPPINCLUDE} -o $@ $< ${SRC}

r-%-1: day%-1.out
	./$^ < $(INPUT)/day$*.txt

r-%-2: day%-2.out
	./$^ < $(INPUT)/day$*.txt

run-test:
ifdef EXE
	@if [ -f "$(TESTTMP)" ]; then ./$(EXE) < "$(TESTTMP)"; \
	elif [ -f "$(TEST)" ]; then ./$(EXE) < "$(TEST)"; \
	else echo "$(TEST)" not found; \
	fi
else
	@echo EXE not defined
endif

t%:
	@make -s TESTTMP=$(INPUT)/tmp.txt d$*

d%:
	@if [ -f "day$*-1.cpp" ]; then                                    \
		make day$*-1.out >/dev/null;                              \
		echo -n "part 1: ";                                       \
		make -s EXE=day$*-1.out TEST=$(INPUT)/day$*.txt run-test; \
	fi
	@if [ -f "day$*-2.cpp" ]; then                                    \
		make day$*-2.out >/dev/null;                              \
		echo -n "part 2: ";                                       \
		make -s EXE=day$*-2.out TEST=$(INPUT)/day$*.txt run-test; \
	fi

clean:
	$(RM) -r core *~ *.o *.out *.exe
