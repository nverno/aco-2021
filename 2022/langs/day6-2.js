#! /usr/bin/env node
'use strict';

const readline = require('readline');
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false,
});

const SZ = 14;

rl.on('line', (line) => {
  let cnt = 0;
  let m = {};
  for (let i = 0; i < line.length; i++) {
    if (m[line[i]]) m[line[i]]++;
    else m[line[i]] = 1, cnt++;
    if (i >= SZ && --m[line[i-SZ]] == 0) --cnt;
    if (cnt == SZ) {
      console.log('Part 2:', i+1);
      break;
    }
  }
});

rl.once('close', () => {});

