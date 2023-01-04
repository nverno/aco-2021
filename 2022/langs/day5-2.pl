#!/usr/bin/perl -w

use strict;
use warnings;
use 5.014;
use utf8;

my $COLS = 9;
my %stacks;
  
while (my $line = <STDIN>) {
  last unless $line =~ /^\s*\[/;
  for (my $i = 1; $i < length($line); $i += 4) {
    if (substr($line, $i, 1) ne ' ') {
      $stacks{int($i/4)} .= substr($line, $i, 1);
    }
  }
}
for my $k (keys %stacks) {
  $stacks{$k} = reverse($stacks{$k});
}
# print "$_ => $stacks{$_}\n" for sort {$a <=> $b} keys %stacks;

while (<STDIN>) {
  next unless $_ =~ /move (\d+) from (\d+) to (\d+)/;
  my $cnt = $1;
  my $str = substr $stacks{$2-1}, -$cnt;
  $stacks{$3-1} .= $str;
  $stacks{$2-1} = substr $stacks{$2-1}, 0, length($stacks{$2-1})-$cnt;
}

print 'Part 2: ';
print substr($stacks{$_}, -1)
  for sort {$a <=> $b} keys %stacks;
print "\n";
