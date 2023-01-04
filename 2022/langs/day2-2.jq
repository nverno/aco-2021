def part2(s): [s | explode | last -= 88 | (first+1+[-1,0,1][last]) % 3 + 1 + last*3] | add;
part2(inputs)
