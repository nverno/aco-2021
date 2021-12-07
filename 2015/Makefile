CC = g++
SRC = ../lib/aoc.cpp
CPPINCLUDE = -I../lib
CXXFLAGS += -Wall -Wshadow -fsanitize=address -fsanitize=undefined -O2 -g -std=c++17
INPUT = $(CURDIR)/input

DAYS = $(wildcard *.cpp)
DAY = $(basename $(wildcard day$(1)*))

RUN = ./$(1) < $(INPUT)/day$(2).txt
BUILD = $(CC) ${CXXFLAGS} ${CPPINCLUDE} -o $(1) $(2) ${SRC}

%.out: %.cpp
	$(CC) ${CXXFLAGS} ${CPPINCLUDE} -o $@ $< ${SRC}

r-%-1: day%-1.out
	./$^ < $(INPUT)/day$*.txt

r-%-2: day%-2.out
	./$^ < $(INPUT)/day$*.txt

d%:
	@if [ -f "day$*-1.cpp" ]; then              \
		make day$*-1.out >/dev/null;        \
		echo -n "part 1: ";                 \
		./day$*-1.out < $(INPUT)/day$*.txt; \
	fi
	@if [ -f "day$*-2.cpp" ]; then              \
		make day$*-2.out >/dev/null;        \
		echo -n "part 2: ";                 \
		./day$*-2.out < $(INPUT)/day$*.txt; \
	fi

clean:
	$(RM) -r core *~ *.o *.out *.exe
