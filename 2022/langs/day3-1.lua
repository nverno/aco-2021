#!/usr/bin/env lua
function isupper(ch) return string.upper(ch) == ch end

function part1()
  local res = 0
  while true do
    line = io.stdin:read()
    if line == nil then break end

    local n, a, b = #line, {}, {}
    for i = 1, #line do
      local c = line:sub(i,i)
      if i <= n/2 then
        a[c] = true
      else
        b[c] = true
      end
    end
    -- for c in line:gmatch"." do
    --   
    -- end

    for c,x in pairs(a) do
      if b[c] then
        if isupper(c) then
          res = res + 27 + (string.byte(c) - string.byte('A'))
        else
          res = res + 1 + (string.byte(c) - string.byte('a'))
        end
        break
      end
    end
  end
  print("Part 1: ", res)
end

part1()
