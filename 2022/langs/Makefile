SHELL   = /bin/bash
ROOTDIR = $(CURDIR)

INPUT ?= $(CURDIR)/../input

all:
	@

d1:
	@./day1.bash < ${INPUT}/day1.txt

d2:
	@echo -n "Part 1: "
	@jq -nRf ./day2-1.jq ${INPUT}/day2.txt
	@echo -n "Part 2: "
	@jq -nRf ./day2-2.jq ${INPUT}/day2.txt

d3:
	@./day3-1.lua < ${INPUT}/day3.txt
	@./day3-2.lua < ${INPUT}/day3.txt

d4:
	@./day4-1.awk < ${INPUT}/day4.txt
	@./day4-2.awk < ${INPUT}/day4.txt

d5:
	@./day5-1.pl < ${INPUT}/day5.txt
	@./day5-2.pl < ${INPUT}/day5.txt

d6:
	@./day6-1.js < ${INPUT}/day6.txt
	@./day6-2.js < ${INPUT}/day6.txt

clean:
	$(RM) -r core *~ *.o *.out *.exe 

distclean: clean
	$(RM)
