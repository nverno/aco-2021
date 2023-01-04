#!/usr/bin/awk -f

BEGIN { res = 0 }
match($0,/([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)/,l) {
    if ((l[1] <= l[3] && l[2] >= l[4]) || (l[3] <= l[1] && l[4] >= l[2])) {
        res++
    }
}
END { print "Part 1: " res }
