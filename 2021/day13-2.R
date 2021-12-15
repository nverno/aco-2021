#!/usr/bin/env Rscript
dat <- read.table(file="input/day13-2.txt", header=FALSE)
plot(dat[, 1], -dat[, 2], pch="#")
